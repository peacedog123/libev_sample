# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

# - Find LIBEV (ev++.h, libev.a, and libev.so)
# This module defines
#  LIBEV_INCLUDE_DIR, directory containing headers
#  LIBEV_SHARED_LIB, path to libev's shared library
#  LIBEV_STATIC_LIB, path to libev's static library
#  LIBEV_FOUND, whether libev has been found

find_path(ZOOKEEPER_INCLUDE_DIR libev/ev++.h)
find_library(ZOOKEEPER_STATIC_LIB libzookeeper_mt.a)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZOOKEEPER REQUIRED_VARS
  ZOOKEEPER_STATIC_LIB ZOOKEEPER_INCLUDE_DIR)

