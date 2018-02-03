#include <gtest/gtest.h>

#include <whiskey/Unicode/IStreamByteInStream.hpp>

using namespace whiskey;

TEST(Unicode_Unit_IStreamByteInStream, Empty) {
  std::stringstream ss;
  IStreamByteInStream bs(ss);

  ASSERT_FALSE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 0);
  ASSERT_EQ(bs.eatChar(), 0);

  ASSERT_FALSE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 0);
  ASSERT_EQ(bs.eatChar(), 0);
}

TEST(Unicode_Unit_IStreamByteInStream, Simple) {
  std::stringstream ss("hello");
  IStreamByteInStream bs(ss);

  ASSERT_TRUE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 'h');
  ASSERT_EQ(bs.eatChar(), 'h');

  ASSERT_TRUE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 'e');
  ASSERT_EQ(bs.eatChar(), 'e');

  ASSERT_TRUE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 'l');
  ASSERT_EQ(bs.eatChar(), 'l');

  ASSERT_TRUE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 'l');
  ASSERT_EQ(bs.eatChar(), 'l');

  ASSERT_TRUE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 'o');
  ASSERT_EQ(bs.eatChar(), 'o');

  ASSERT_FALSE(bs.isMore());
  ASSERT_EQ(bs.getChar(), 0);
  ASSERT_EQ(bs.eatChar(), 0);
}
