/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "impl/EnumDetails.h"

/* MY_ENUM_DEF(NAME, [INT_TYPE], ARGS ...)

  Enum type definition. Can be in global, and namespace scope only. See MY_ENUM
  below for details. */
#define MY_ENUM_DEF(NAME, ...) MY_ENUM_DEF_IMPL(NAME, __VA_ARGS__)

/* MY_ENUM_ALIAS(NAME)

  Enum type alias. Can be in any scope. See MY_ENUM below for details. */
#define MY_ENUM_ALIAS(NAME) using NAME = enum_wrapper_::NAME##Impl

/* MY_ENUM(NAME, [INT_TYPE], ARGS ...)
  Enum type. Can be in global, and namespace scope only.

      NAME:     Name of the enum class.
      INT_TYPE: integral type, optional argument which defaults to ``int``.
      ARGS:     Tuple of enums. Could be just names, such as (foo, bar), or
                also name/value pairs, such as ((one,1), (two,2)).

  For example ``MY_ENUM(FooBar, int, (foo, bar));`` defines an enum class

    enum class FooBar : int {
      foo,
      bar
    };

  with the following free functions:

    // Returns corresponding string of given value
    //
    // Preconditions: value must be a valid enum value, i.e. FooBar::foo, or
    //                FooBar::bar.
    //
    std::string toString(FooBar value);

    // Returns corresponding string of given value, or `defaultIfInvalid` if the
    // given value does not correspond to an enum element.
    //
    std::string tryToString(FooBar value, string_view defaultIfInvalid);

    // Returns corresponding string view of given value
    //
    // Preconditions: value must be a valid enum value, i.e. FooBar::foo, or
    //                FooBar::bar.
    //
    string_view toStringView(FooBar value);

    // Returns pretty string representation of given value
    //
    // Preconditions: value must be a valid enum value, i.e. FooBar::foo, or
    //                FooBar::bar.
    //
    std::string toPretty(FooBar value);

    // Sets enum given corresponding string, if string is valid (i.e. "foo" or
    // "bar"). Returns false otherwise.
    //
    bool trySetFromString(FooBar& value, string_view str);

    // Sets enum given corresponding string, if string matches case-insensitive
    // (i.e. "foo" and "Foo" will both match). Returns false otherwise.
    //
    bool trySetFromStringCaseInsensitive(FooBar& value, string_view str);

    // Returns count of enum type. First argument is needed for ADL only.
    //
    constexpr size_t getCount(FooBar) {
      return 2;
    }

    // Returns string views of enum type. First argument is needed for ADL only.
    std::array<string_view, 2> getStrings(FooBar) {
      return {"foo", "bar"};
    }

    // Returns string view of enum names. First argument is needed for ADL only.
    string_view getStringOfNames(FooBar) {
      return "foo, bar";
    }

    // Returns values of enum type. First argument is needed for ADL only.
    constexpr std::array<int, 2> getValues(FooBar) {
      return {0, 1};
    }

    // Returns elements of enum type. First argument is needed for ADL only.
    constexpr std::array<FooBar, 2> getElements(FooBar) {
      return {FooBar::foo, FooBar::bar};
    }

    // Returns the position of enum value in the enum class. This is the inverse
    // of `getValues(FooBar)[i]`.
    constexpr size_t getPosition(FooBar value) {
      switch(value) {
        case FooBar::foo: { return 0; }
        case FooBar::bar: { return 1; }
      }
    }

    // Returns string representation of type name. First argument is needed for
    // ADL only.
    string_view getTypeName(FooBar) {
      return "FooBar";
    }
*/
#define MY_ENUM(NAME, ...)       \
  MY_ENUM_DEF(NAME, __VA_ARGS__) \
  MY_ENUM_ALIAS(NAME)

template <typename T>
std::optional<T> tryFromString(MY_ENUM_STRING_VIEW str) {
  T value;
  const bool success = trySetFromString(value, str);
  return success ? std::optional<T>(value) : std::nullopt;
}

template <typename T>
std::optional<T> tryFromStringCaseInsensitive(MY_ENUM_STRING_VIEW str) {
  T value;
  const bool success = trySetFromStringCaseInsensitive(value, str);
  return success ? std::optional<T>(value) : std::nullopt;
}
