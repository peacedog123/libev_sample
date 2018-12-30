#include "io_loop.h"

#include <glog/logging.h>

#include "util.h"

IOLoop::IOLoop() : loop_(ev::AUTO) {

}

bool IOLoop::StartLoop() {
  DCHECK(thread_ptr_ == nullptr);

  // add the async
  async_.set(loop_);
  async_.set<IOLoop, &IOLoop::AsyncHandler>(this);
  async_.start();

  // start the thread TODO
  thread_ptr_.reset(new std::thread(&IOLoop::RunLoopThread, this));
  LOG(WARNING) << "RunLoopThread started...";
  return true;
}

void IOLoop::AsyncHandler(ev::async& /*watcher*/, int /*revents*/) {
  // get the fd vector
  std::vector<int> fd_vec;
  {
    std::lock_guard<std::mutex> guard(mutex_);
    while (!fd_queue_.empty()) {
      fd_vec.push_back(fd_queue_.front());
      fd_queue_.pop_front();
    }
  }

  // construct the connection
  for (const auto fd : fd_vec) {
    SetNonblocking(fd);
    int64_t next_id = GetNextId();
    Connection::Ptr ptr(new Connection(fd, next_id));
    ptr->EpollRegister(loop_);
    conn_map_.emplace(next_id, ptr);
  }
}

bool IOLoop::RunLoopThread() {
  loop_.loop();
  LOG(WARNING) << "Now exiting the IOLoop...";
  return true;
}

bool IOLoop::AddNewFD(int fd) {
  {
    std::lock_guard<std::mutex> guard(mutex_);
    fd_queue_.push_back(fd);
  }
  async_.send();
  return true;
}
