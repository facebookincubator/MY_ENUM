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

// In Windows, MY_ENUM_O triggers harmless warning in boost macros
// BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY and BOOST_PP_SEQ_DETAIL_EMPTY_SIZE:
// "warning C4003: not enough arguments for function-like macro invocation".
// Frustratingly, disabling the warning directly in in MY_ENUM_O won't actually
// stop the compiler from reporting the warning; the caller needs to disable
// the warning seperately.
#if defined(_MSC_VER) && !defined(__clang__)
#define DISABLE_MY_ENUM_O_WARNINGS \
  __pragma(warning(push)) __pragma(warning(disable : 4003))
#define ENABLE_MY_ENUM_O_WARNINGS __pragma(warning(pop))
#else
#define DISABLE_MY_ENUM_O_WARNINGS
#define ENABLE_MY_ENUM_O_WARNINGS
#endif
