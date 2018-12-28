#include <cstdlib>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(port, 8080, "");

static bool stop = false;

int main(int argc, char* argv[]) {
  // 解析命令行参数
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  // 初始化日志库
  google::InitGoogleLogging(argv[0]);

  // server socket
  int fd = socket(PF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    LOG(ERROR) << "Server socket create failed.";
    exit(1);
  }

  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = PF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(FLAGS_port);

  if (bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    LOG(ERROR) << "Server bind address error.";
    exit(1);
  }

  if (listen(fd, 5) == -1) {
    LOG(ERROR) << "Server listen error.";
    exit(1);
  }


  while (!stop) {
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    int client_length;
    int sock = accept(fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_length);
    if (sock == -1) {
      continue;
    }

    LOG(ERROR) << "Accept fd: " << sock;
    // TODO else put to queue
  }

  return 0;
}
