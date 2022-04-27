/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <ostream>

#include "EnumFlags.h"

#define MY_ENUMFLAGS_OSTREAM_OVERLOAD(NAME)                             \
  namespace enum_wrapper_ {                                             \
  inline std::ostream &operator<<(std::ostream &os, NAME##Impl value) { \
    os << toPretty(value);                                              \
    return os;                                                          \
  }                                                                     \
  }  // namespace enum_wrapper_

// Convenience marco which defines the enum flags plus alias and adds the
// ostream overload.
#define MY_ENUMFLAGS_O(EnumName, UINT_TYPE, ...)  \
  MY_ENUMFLAGS(EnumName, UINT_TYPE, __VA_ARGS__); \
  MY_ENUMFLAGS_OSTREAM_OVERLOAD(EnumName)

// Convenience marco which defines the enum flags and adds the ostream overload.
#define MY_ENUMFLAGS_DEF_O(EnumName, UINT_TYPE, ...)  \
  MY_ENUMFLAGS_DEF(EnumName, UINT_TYPE, __VA_ARGS__); \
  MY_ENUMFLAGS_OSTREAM_OVERLOAD(EnumName)
