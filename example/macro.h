#pragma once

#define DISALLOW_COPY_AND_ASSIGN(CLASS_NAME)  \
  CLASS_NAME(const CLASS_NAME&) = delete;     \
  void operator=(const CLASS_NAME&) = delete
