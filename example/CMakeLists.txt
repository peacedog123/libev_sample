PROJECT(echo_server)

SET(SRC_LIST_SERVER echo_server.cc server.cc io_loop.cc util.cc connection.cc)

ADD_EXECUTABLE(echo_server ${SRC_LIST_SERVER})

TARGET_LINK_LIBRARIES(echo_server  ${DYNAMIC_LIB})
