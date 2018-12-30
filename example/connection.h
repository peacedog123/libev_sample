#pragma once

#include <libev/ev++.h>

#include <deque>
#include <memory>
#include <string>

#include "macro.h"

class Connection {
 public:
  typedef std::shared_ptr<Connection> Ptr;

  Connection(int fd, int64_t id);

  bool EpollRegister(ev::loop_ref& loop);

  // libev callback when data is available to read.
  void ReadHandler(ev::io &watcher, int revents);

  // libev callback when we may write to the socket.
  void WriteHandler(ev::io &watcher, int revents);

 private:
  int fd_ { -1 };
  int64_t id_ { -1 };

  ev::io read_io_;
  ev::io write_io_;

  std::string out_buf_;
  std::string in_buf_;

  bool is_loop_registered_ { false };

  DISALLOW_COPY_AND_ASSIGN(Connection);
};
