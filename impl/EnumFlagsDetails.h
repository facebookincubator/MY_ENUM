/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <array>
#include <string>
#include <type_traits>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/pop_front.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

#include "CompilerAttributes.h"
#include "StringView.h"

// Output: , ${FLAG} = (1 << ($I + 1))
#define MY_ENUMFLAGS_DETAILS_OP_INIT_FLAG(dummy1, dummy2, I, FLAG) \
  , FLAG = (1 << (I + 1))

// Input:  (A, B, C, D)
// Output: A=1, B=(1<<1), C=(1<<2), D=(1<<3)
#define MY_ENUMFLAGS_DETAILS_FLAG_DEFINITIONS(...)                 \
  BOOST_PP_TUPLE_ELEM(0, __VA_ARGS__) = 1 BOOST_PP_SEQ_FOR_EACH_I( \
      MY_ENUMFLAGS_DETAILS_OP_INIT_FLAG, _,                        \
      BOOST_PP_SEQ_POP_FRONT(BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__)))

// Output:
//   if (str == "${FLAGS}") {
//     value = ${TYPE}:${FLAG};
//     return true;
//   }
#define MY_ENUMFLAG_DETAILS_OP_SET_ENUM_FROM_STRING(dummy1, TYPE, FLAG) \
  if (str == BOOST_PP_STRINGIZE(FLAG)) {                                \
    value = value | TYPE::FLAG;                                         \
    return true;                                                        \
  }

// Output:
//   case ${TYPE}::$FLAG}: {
//     static_assert(
//         std::popcount(uint64_t(${TYPE}::${FLAG})) == 1,
//         "${FLAG} must be a single bit flag");
//     return true;
//   }
#if (defined __linux__ || defined __APPLE__)
#define MY_ENUMFLAG_DETAILS_OP_SINGLE_FLAG_CHECK(dummy1, TYPE, FLAG)      \
  case TYPE::FLAG: {                                                      \
    static_assert(__builtin_popcount(uint64_t(TYPE::FLAG)) == 1,          \
                  BOOST_PP_STRINGIZE(FLAG) " must be a single bit flag"); \
    return true;                                                          \
  }
#else
#define MY_ENUMFLAG_DETAILS_OP_SINGLE_FLAG_CHECK(dummy1, TYPE, FLAG) \
  case TYPE::FLAG: {                                                 \
    return true;                                                     \
  }
#endif

// Output:
//   if (hasMask(value, ${TYPE}::${FLAG})) {
//      strings.push_back("${FLAG}");
//   }
#define MY_ENUMFLAG_DETAILS_OP_PUSHBACK_STRING(dummy1, TYPE, FLAG) \
  if (hasMask(value, TYPE::FLAG)) {                                \
    strings.push_back(BOOST_PP_STRINGIZE(FLAG));                   \
  }

// Output:
//   if (hasMask(value, ${TYPE}::${FLAG})) {
//      prettySet += "${FLAG}, ";
//   }
#define MY_ENUMFLAG_DETAILS_OP_STRING_FOR_FLAG(dummy1, TYPE, FLAG)  \
  if (hasMask(value, TYPE::FLAG)) {                                 \
    prettySet += BOOST_PP_STRINGIZE(FLAG) " (=" + std::to_string(uint64_t(TYPE::FLAG)) + "), "; \
  }

// Output: ", ${STRING}"
#define MY_ENUMFLAGS_DETAILS_OP_COMMA_STRING(dummy1, dummy2, STRING) \
  , BOOST_PP_STRINGIZE(STRING)

// Input: (A, B, C)
// Output: "A", "B", "C"
#define MY_ENUMFLAGS_DETAILS_COMMA_SEP_STRINGS(...)       \
  BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, __VA_ARGS__)) \
  BOOST_PP_SEQ_FOR_EACH(                                  \
      MY_ENUMFLAGS_DETAILS_OP_COMMA_STRING, _,            \
      BOOST_PP_SEQ_POP_FRONT(BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__)))

// Output: ", ${STRING}"
#define MY_ENUMFLAGS_DETAILS_OP_COMMA_VALUE_STRING(dummy1, dummy2, STRING) \
  ", " BOOST_PP_STRINGIZE(STRING)

// Input: (A, B, C)
// Output: "A, B, C"
#define MY_ENUMFLAGS_DETAILS_CSV_STRING(...)              \
  BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, __VA_ARGS__)) \
  BOOST_PP_SEQ_FOR_EACH(                                  \
      MY_ENUMFLAGS_DETAILS_OP_COMMA_VALUE_STRING, _,      \
      BOOST_PP_SEQ_POP_FRONT(BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__)))

// Output: , uint64_t(${TYPE}::${VAL})
#define MY_ENUMFLAGS_DETAILS_OP_COMMA_INT(dummy1, TYPE, VAL) \
  , uint64_t(TYPE::VAL)

// Input:  (A, B, C)
// Output: 1, 2, 4
//
// Note: Here, "1, 2, 4" are the values of "A, B, C".
#define MY_ENUMFLAGS_DETAILS_COMMA_SEP_INTS(TYPE, ...)                       \
  uint64_t(TYPE::BOOST_PP_TUPLE_ELEM(0, __VA_ARGS__)) BOOST_PP_SEQ_FOR_EACH( \
      MY_ENUMFLAGS_DETAILS_OP_COMMA_INT, TYPE,                               \
      BOOST_PP_SEQ_POP_FRONT(BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__)))

#define MY_ENUMFLAGS_DEF_IMPL(NAME, UINT_TYPE, ...)                           \
  namespace enum_wrapper_ {                                                   \
                                                                              \
  static_assert(                                                              \
      std::is_unsigned<UINT_TYPE>::value,                                     \
      BOOST_PP_STRINGIZE(UINT_TYPE) " must be an unsigned integer type");     \
                                                                              \
  enum class NAME##Impl : UINT_TYPE{                                          \
      none = 0u, MY_ENUMFLAGS_DETAILS_FLAG_DEFINITIONS(__VA_ARGS__)};         \
                                                                              \
  NAME##Impl inline operator|(NAME##Impl left, NAME##Impl right) {            \
    return NAME##Impl(UINT_TYPE(left) | UINT_TYPE(right));                    \
  }                                                                           \
                                                                              \
  NAME##Impl inline operator&(NAME##Impl left, NAME##Impl right) {            \
    return NAME##Impl(UINT_TYPE(left) & UINT_TYPE(right));                    \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline bool trySetFlagFromString(                      \
      NAME##Impl &value, const std::string &str) {                            \
    BOOST_PP_SEQ_FOR_EACH(MY_ENUMFLAG_DETAILS_OP_SET_ENUM_FROM_STRING,        \
                          NAME##Impl, BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__))     \
    return false;                                                             \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline bool hasMask(NAME##Impl value,                  \
                                           NAME##Impl mask) {                 \
    return (value & mask) == mask;                                            \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline void setMask(NAME##Impl &value,                 \
                                           NAME##Impl mask) {                 \
    value = value | mask;                                                     \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline void clearMask(NAME##Impl &value,               \
                                             NAME##Impl mask) {               \
    value = value & NAME##Impl(~UINT_TYPE(mask));                             \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline void toggleMask(NAME##Impl &value,              \
                                              NAME##Impl mask) {              \
    value = NAME##Impl(UINT_TYPE(value) ^ UINT_TYPE(mask));                   \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline bool isSingleFlag(NAME##Impl value) {           \
    switch (value) {                                                          \
      BOOST_PP_SEQ_FOR_EACH(MY_ENUMFLAG_DETAILS_OP_SINGLE_FLAG_CHECK,         \
                            NAME##Impl, BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__))   \
      case NAME##Impl::none:                                                  \
        break;                                                                \
    }                                                                         \
    return false;                                                             \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline std::vector<std::string> toStrings(             \
      NAME##Impl value) {                                                     \
    std::vector<std::string> strings;                                         \
    BOOST_PP_SEQ_FOR_EACH(MY_ENUMFLAG_DETAILS_OP_PUSHBACK_STRING, NAME##Impl, \
                          BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__))                 \
    return strings;                                                           \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED inline std::string toPretty(NAME##Impl value) {        \
    std::string prettySet("{");                                               \
    BOOST_PP_SEQ_FOR_EACH(MY_ENUMFLAG_DETAILS_OP_STRING_FOR_FLAG, NAME##Impl, \
                          BOOST_PP_TUPLE_TO_SEQ(__VA_ARGS__))                 \
    prettySet += "} (=" + std::to_string(UINT_TYPE(value)) + ")";             \
    return prettySet;                                                         \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED MY_ENUM_NODISCARD constexpr size_t getCount(           \
      NAME##Impl) {                                                           \
    return BOOST_PP_TUPLE_SIZE(__VA_ARGS__);                                  \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED                                                        \
  MY_ENUM_NODISCARD inline std::array<MY_ENUM_STRING_VIEW,                    \
                                      BOOST_PP_TUPLE_SIZE(__VA_ARGS__)>       \
  getNames(NAME##Impl) {                                                      \
    return {MY_ENUMFLAGS_DETAILS_COMMA_SEP_STRINGS(__VA_ARGS__)};             \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED MY_ENUM_NODISCARD inline MY_ENUM_STRING_VIEW           \
  getStringOfNames(NAME##Impl) {                                              \
    return MY_ENUMFLAGS_DETAILS_CSV_STRING(__VA_ARGS__);                      \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED                                                        \
  MY_ENUM_NODISCARD constexpr std::array<UINT_TYPE,                           \
                                         BOOST_PP_TUPLE_SIZE(__VA_ARGS__)>    \
  getValues(NAME##Impl) {                                                     \
    return {MY_ENUMFLAGS_DETAILS_COMMA_SEP_INTS(NAME##Impl, __VA_ARGS__)};    \
  }                                                                           \
                                                                              \
  MY_ENUM_MAYBE_UNUSED MY_ENUM_NODISCARD inline MY_ENUM_STRING_VIEW           \
  getTypeName(NAME##Impl) {                                                   \
    return BOOST_PP_STRINGIZE(NAME);                                          \
  }                                                                           \
  }  // namespace enum_wrapper_
