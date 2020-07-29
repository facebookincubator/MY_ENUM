// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <ostream>

#include "Enum.h"

#define MY_ENUM_OSTREAM_OVERLOAD(EnumName)                                  \
  namespace enum_wrapper_ {                                                 \
  inline std::ostream &operator<<(std::ostream &os, EnumName##Impl value) { \
    os << toPretty(value);                                                  \
    return os;                                                              \
  }                                                                         \
  }  // namespace enum_wrapper_

// Convenience marco which defines the enum plus alias and adds the ostream
// overload.
#define MY_ENUM_O(EnumName, ...)  \
  MY_ENUM(EnumName, __VA_ARGS__); \
  MY_ENUM_OSTREAM_OVERLOAD(EnumName)

// Convenience marco which defines the enum and adds the ostream overload.
#define MY_ENUM_DEF_O(EnumName, ...)  \
  MY_ENUM_DEF(EnumName, __VA_ARGS__); \
  MY_ENUM_OSTREAM_OVERLOAD(EnumName)
