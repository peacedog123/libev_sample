#pragma once

#include <memory>
#include <thread>

#include <libev/ev++.h>

class Connection;

class IOLoop {
 public:
  IOLoop();

  // start eventloop in loop thread
  bool StartLoop();

  bool AddNewFD(int fd);

  // In Loop Thread
  bool RunLoopThread();
  void AsyncHandler(ev::async& /*watcher*/, int /*revents*/);

 private:
  // the loop thread
  std::shared_ptr<std::thread> thread_ptr_ { nullptr };

  // our epoll object (or kqueue, etc).
  ev::dynamic_loop loop_;

  // Used by other threads to notify the reactor thread
  ev::async async_;
};
