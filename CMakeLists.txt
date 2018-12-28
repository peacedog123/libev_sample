cmake_minimum_required(VERSION 2.8)
PROJECT(libev_sample)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
find_package(LibEv REQUIRED)
if (NOT LIBEV_INCLUDE_DIR)
  message(FATAL_ERROR "Fail to find libev lib")
endif()

find_package(GLog REQUIRED)
if (NOT GLOG_INCLUDE_DIR)
  message(FATAL_ERROR "Fail to find glog lib")
endif()

find_package(GFlags REQUIRED)
if (NOT GFLAGS_INCLUDE_DIR)
  message(FATAL_ERROR "Fail to find gflags lib")
endif()

include_directories(${GLOG_INCLUDE_DIR})
include_directories(${GFLAGS_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(DYNAMIC_LIB
    ${GLOG_SHARED_LIB}
    ${GFLAGS_SHARED_LIB}
    ev
    pthread
    rt
)

ADD_SUBDIRECTORY(example)
