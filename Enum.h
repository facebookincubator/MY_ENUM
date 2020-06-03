// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

/// https://fburl.com/magic-enum

#pragma once

#include "impl/EnumDetails.h"

/* Enum type definition. Can be in global, and namespace scope only. See MY_ENUM for details. */
#define MY_ENUM_DEF(EnumName, ...) MY_ENUM_DEF_IMPL(EnumName, __VA_ARGS__)

/* Enum type alias. Can be in any scope. See MY_ENUM for details. */
#define MY_ENUM_ALIAS(EnumName) using EnumName = enum_wrapper_::EnumName##Impl

/* Enum type. Can be in global, and namespace scope only.

  For example ``MY_ENUM(Enums, int, (foo, bar));`` defines an enum class

    enum class Enums : int {
      foo,
      bar
    };

  with the following free functions:

    // Returns corresponding string of given value
    //
    // Preconditions: value must be a valid enum value, i.e. Enums::foo, or Enums::bar.
    //
    std::string toString(Enums value);

    // Returns corresponding string view of given value
    //
    // Preconditions: value must be a valid enum value, i.e. Enums::foo, or Enums::bar.
    //
    constexpr folly::StringPiece toString(Enums value);

    // Returns pretty string representation of given value
    //
    // Preconditions: value must be a valid enum value, i.e. Enums::foo, or Enums::bar.
    //
    std::string toPretty(Enums value);

    // Sets enum given corresponding string, if string is valid (i.e. "foo" or "bar").
    // Returns false otherwise.
    //
    bool trySetFromString(Enums& value, std::string str);

    // Return count of enum type. First argument is needed for ADL only.
    //
    size_t getCount(Enums) {
      return 2;
    }

    // Return string views of enum type. First argument is needed for ADL only.
    constexpr std::array<folly::StringPiece, 2> getStrings(Enums) {
      return {"foo", "bar"};
    }

    // Return values of enum type. First argument is needed for ADL only.
    constexpr std::array<int, 2> getValues(Enums) {
      return {0, 1};
    }

    // Returns the position of enum value in the enum class. This is the inverse of
    // `getValues(Enums)[i]`.
    size_t getPosition(Enums value) {
      switch(value) {
        case Enums::foo: { return 0; }
        case Enums::bar: { return 1; }
      }
    }

    // Return string representation of type name. First argument is needed for ADL only.
    constexpr folly::StringPiece getTypeName(Enums) {
      return "Enums";
    }
*/
#define MY_ENUM(EnumName, ...)       \
  MY_ENUM_DEF(EnumName, __VA_ARGS__) \
  MY_ENUM_ALIAS(EnumName)
