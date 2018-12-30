#pragma once

#include <atomic>
#include <deque>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

#include <libev/ev++.h>

#include "connection.h"

class IOLoop {
 public:
  IOLoop();

  // start eventloop in loop thread
  bool StartLoop();

  bool AddNewFD(int fd);

  // In Loop Thread
  bool RunLoopThread();
  void AsyncHandler(ev::async& /*watcher*/, int /*revents*/);

  int64_t GetNextId() {
    return ++next_id_;
  }

 private:
  // the loop thread
  std::shared_ptr<std::thread> thread_ptr_ { nullptr };

  std::mutex mutex_;
  std::deque<int> fd_queue_;

  std::atomic<int64_t> next_id_ { 0 };
  std::unordered_map<int64_t, Connection::Ptr> conn_map_;

  // our epoll object (or kqueue, etc).
  ev::dynamic_loop loop_;

  // Used by other threads to notify the reactor thread
  ev::async async_;

};
