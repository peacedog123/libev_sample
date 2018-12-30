#pragma once

#include <libev/ev++.h>

#include "io_loop.h"
#include "macro.h"

class Server {
 public:
  Server();
  ~Server();

  bool InitDispatcher();

  // listen on the port - blocking
  void Run(int port);

 private:
  void HandleRead(ev::io &watcher, int revents);
  void HandleSignal(ev::sig &watcher, int signo);

 private:
  ev::dynamic_loop loop_;
  int server_fd_ { -1 };

  ev::io read_io_;
  ev::sig sig_;

  // for handling the incoming requests
  IOLoop io_loop_;

  DISALLOW_COPY_AND_ASSIGN(Server);
};
