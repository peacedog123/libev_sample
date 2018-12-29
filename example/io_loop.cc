#include "io_loop.h"

#include <glog/logging.h>

IOLoop::IOLoop() : loop_(ev::AUTO) {

}

bool IOLoop::StartLoop() {
  DCHECK(thread_ptr_ == nullptr);

  // add the async
  async_.set(loop_);
  async_.set<IOLoop, &IOLoop::AsyncHandler>(this);
  async_.start();

  // start the thread TODO
  //thread_ptr_.reset(new Thread(
  return true;
}

void IOLoop::AsyncHandler(ev::async& /*watcher*/, int /*revents*/) {
  // TODO

}

bool IOLoop::RunLoopThread() {
  // TODO
  return true;
}

bool AddNewFD(int fd) {
  // TODO
  return true;
}
