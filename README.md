# libev_sample

根据工作中使用的场景，利用libev作为服务端，完成了一个echo_server

工作模型是Reactor方式

example/server.cc - 负责创建服务端套接字来接收请求accept, 同时接收SIGINT来关闭服务
example/io_loop.cc - 负责所有connection的读写loop(worker)
example/connection.cc - 每个连接上来的请求会创建一个Connection, 内部会处理tcp收发包。协议采用简单的文本协议, "\r\n"作为分隔符(模拟http), 服务端会在每个request里面加上"Hello: "的头部作为echo response

TODO
更高效的in_buf/out_buf
Connection的动态删除
IOLoop可以多线程(多个worker)
服务整体的优雅关闭
