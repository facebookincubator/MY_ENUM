// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#define MY_ENUM_ABORT(strlit, ...)                                     \
  /* This does not work in constexpr context for some environments. */ \
  /* Hence we deactivate printf for now. */                            \
  /* fmt::printf("{}:{}" strlit, __FILE__, __LINE__, __VA_ARGS__); */  \
  std::abort()
