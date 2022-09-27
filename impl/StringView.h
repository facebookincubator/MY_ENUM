/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#ifdef MY_ENUM_USE_STD_STRING_VIEW
#include <string_view>

#define MY_ENUM_STRING_VIEW std::string_view
#define MY_ENUM_STRING_VIEW_TO_STRING(sv) (std::string(sv))

#else
#include <fmt/core.h>

#define MY_ENUM_STRING_VIEW fmt::string_view
#define MY_ENUM_STRING_VIEW_TO_STRING(sv) (std::string(sv.data(), sv.size()))

#endif
