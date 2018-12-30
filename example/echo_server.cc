#include <gflags/gflags.h>
#include <glog/logging.h>

#include "server.h"

DEFINE_int32(port, 8080, "");

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  Server server;
  server.Run(FLAGS_port);

  LOG(WARNING) << "Server exiting now...";

  return 0;
}
