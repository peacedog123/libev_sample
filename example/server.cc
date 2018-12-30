#include "server.h"

#include <cstdlib>
#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <libev/ev++.h>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "io_loop.h"
#include "util.h"

Server::Server() : loop_(ev::AUTO) {
}

Server::~Server() {
  if (server_fd_ >= 0) {
    close(server_fd_);
  }
}

bool Server::InitDispatcher() {
  // TODO
  return true;
}

void Server::HandleRead(ev::io& watcher, int revents) {
  LOG(WARNING) << "Received io: " << revents;
  while(true) {
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    int client_length;
    int sock = accept(server_fd_, (struct sockaddr*)&client_addr, (socklen_t*)&client_length);
    if (sock == -1 && errno == EAGAIN) {
      LOG(WARNING) << "Nothing to read, return...";
      break;
    }

    LOG(WARNING) << "Received fd: " << sock;
    io_loop_.AddNewFD(sock);
  }
}

void Server::HandleSignal(ev::sig& watcher, int signo) {
  LOG(WARNING) << "Received sig: " << signo;
  loop_.break_loop(ev::ALL);
}

void Server::Run(int port) {
  // server socket
  server_fd_ = socket(PF_INET, SOCK_STREAM, 0);
  if (server_fd_ == -1) {
    LOG(ERROR) << "Server socket create failed.";
    exit(1);
  }

  int flag = SetNonblocking(server_fd_);
  LOG(WARNING) << "SetNonblocking flag: " << flag;

  // bind to localaddress
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = PF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if (bind(server_fd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    LOG(ERROR) << "Server bind address error.";
    exit(1);
  }

  if (listen(server_fd_, 5) == -1) {
    LOG(ERROR) << "Server listen error.";
    exit(1);
  }

  // set the loop
  read_io_.set(loop_);
  read_io_.set(server_fd_, ev::READ);
  read_io_.set<Server, &Server::HandleRead>(this);
  read_io_.start();

  sig_.set(loop_);
  sig_.set<Server, &Server::HandleSignal>(this);
  sig_.start(SIGINT);

  // Start loop
  io_loop_.StartLoop();

  // infinite loop
  loop_.loop();
}
