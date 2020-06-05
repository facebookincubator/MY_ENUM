// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include <sstream>

#include <gtest/gtest.h>

#include "../EnumFlagsO.h"

MY_ENUMFLAGS_O(MyFlags, uint32_t, (foo, bar, daz));

TEST(EnumTest, toString) {
  MyFlags flags = MyFlags::foo;
  std::stringstream out;
  out << flags;
  EXPECT_EQ(out.str(), "{foo (=1), } (=1)");
  flags = MyFlags::none;
  std::stringstream out2;
  out2 << flags;
  EXPECT_EQ(out2.str(), "{} (=0)");
  flags = MyFlags::bar | MyFlags::daz;
  std::stringstream out3;
  out3 << flags;
  EXPECT_EQ(out3.str(), "{bar (=2), daz (=4), } (=6)");
}

TEST(EnumFlags, StringsAndValues) {
  MY_ENUM_STRING_VIEW typeName = getTypeName(MyFlags());
  EXPECT_EQ(typeName, "MyFlags");
  std::array<MY_ENUM_STRING_VIEW, 3> strings = getNames(MyFlags());
  EXPECT_EQ(strings[0], "foo");
  EXPECT_EQ(strings[1], "bar");
  EXPECT_EQ(strings[2], "daz");
  MY_ENUM_STRING_VIEW stringOfStrings = getStringOfNames(MyFlags());
  EXPECT_EQ(stringOfStrings, std::string("foo, bar, daz"));
  std::array<uint32_t, 3> values = getValues(MyFlags());
  EXPECT_EQ(values[0], 1);
  EXPECT_EQ(values[1], 2);
  EXPECT_EQ(values[2], 4);
  EXPECT_EQ(getCount(MyFlags()), 3);
}
