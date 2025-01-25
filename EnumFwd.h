/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
/* MY_ENUM_FWD(NAME)

  A forward declaration of an enum. */
#define MY_ENUM_FWD(NAME)   \
  namespace enum_wrapper_ { \
  enum class NAME##Impl;    \
  }                         \
  using NAME = enum_wrapper_::NAME##Impl
