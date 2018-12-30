#include "connection.h"

#include <string>

#include <glog/logging.h>

Connection::Connection(int fd, int64_t id) : fd_(fd), id_(id) {

}

bool Connection::EpollRegister(ev::loop_ref& loop) {
  write_io_.set(loop);
  write_io_.set(fd_, ev::WRITE);
  write_io_.set<Connection, &Connection::WriteHandler>(this);
  //write_io_.start();

  read_io_.set(loop);
  read_io_.set(fd_, ev::READ);
  read_io_.set<Connection, &Connection::ReadHandler>(this);
  read_io_.start();
  is_loop_registered_ = true;
}

 // libev callback when data is available to read.
void Connection::ReadHandler(ev::io &watcher, int revents) {
  while (true) {
    char buf[1024];
    int num = read(fd_, buf, 1024);
    if (num <= 0) {
      if (read == 0) {
        // TODO, close
      }

      if (errno == EINTR) {
        continue;
      }

      if (errno == EAGAIN) {
        break;
      }
    }
    in_buf_.insert(in_buf_.end(), buf, buf + num);
  }

  // Handle Write
  while (!in_buf_.empty()) {
    std::size_t pos = in_buf_.find("\r\n");
    if (pos == std::string::npos) {
      break;
    }

    out_buf_ = out_buf_ + "Hello: " + in_buf_.substr(0, pos) + "\r\n";
    in_buf_.erase(0, pos + 2);
  }
  if (!out_buf_.empty()) {
    write_io_.start();
  }
}

// libev callback when we may write to the socket.
void Connection::WriteHandler(ev::io &watcher, int revents) {
  LOG(WARNING) << "Something to write...";
  if (out_buf_.empty()) {
    write_io_.stop();
  }

  while (!out_buf_.empty()) {
    ssize_t num = write(fd_, out_buf_.c_str(), out_buf_.size());
    if (num < 0) {
      if (errno == EINTR) {
        continue;
      }

      // other error
    }

    out_buf_ = out_buf_.substr(num);

  }

  write_io_.stop();
}
