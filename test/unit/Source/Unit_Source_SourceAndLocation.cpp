#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Source/Source.hpp>
#include <whiskey/Source/Location.hpp>

using namespace whiskey;

TEST(Unit_Source_SourceAndLocation, Empty) {
  Location loc;

  ASSERT_FALSE(loc.hasSource());

  ASSERT_FALSE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "");
  ASSERT_FALSE(loc.hasPath());

  loc.setPathOverride("asdf");
  ASSERT_TRUE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "asdf");
  ASSERT_TRUE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "asdf");

  loc.setPathOverride();
  ASSERT_FALSE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "");
  ASSERT_FALSE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "");

  ASSERT_FALSE(loc.hasOffset());

  loc.setOffset();
  ASSERT_FALSE(loc.hasOffset());

  loc.setOffset(5);
  ASSERT_TRUE(loc.hasOffset());
  ASSERT_EQ(loc.getOffset(), 5);

  loc.setOffset();
  ASSERT_FALSE(loc.hasOffset());

  ASSERT_FALSE(loc.hasLine());

  loc.setLine();
  ASSERT_FALSE(loc.hasLine());

  loc.setLine(5);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 5);

  loc.setLine();
  ASSERT_FALSE(loc.hasLine());

  ASSERT_FALSE(loc.hasColumn());

  loc.setColumn();
  ASSERT_FALSE(loc.hasColumn());

  loc.setColumn(5);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.setColumn();
  ASSERT_FALSE(loc.hasColumn());

  ASSERT_FALSE(loc.areMoreChars());
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_FALSE(loc.areMoreChars(1000));

  ASSERT_EQ(loc.getChar(), 0);
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_EQ(loc.getChar(1000), 0);

  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
}

TEST(Unit_Source_SourceAndLocation, Unloaded_Empty) {
  Source src;

  ASSERT_FALSE(src.isLoaded());
  ASSERT_STREQ(src.getPath().c_str(), "--");

  Location loc(src);

  ASSERT_TRUE(loc.hasSource());
  ASSERT_FALSE(loc.getSource().isLoaded());
  ASSERT_STREQ(loc.getSource().getPath().c_str(), "--");

  ASSERT_FALSE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "");
  ASSERT_TRUE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "--");

  loc.setPathOverride("asdf");
  ASSERT_TRUE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "asdf");
  ASSERT_TRUE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "asdf");

  loc.setPathOverride();
  ASSERT_FALSE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "");
  ASSERT_TRUE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "--");

  ASSERT_TRUE(loc.hasOffset());
  ASSERT_EQ(loc.getOffset(), 0);

  loc.setOffset();
  ASSERT_FALSE(loc.hasOffset());

  loc.setOffset(5);
  ASSERT_TRUE(loc.hasOffset());
  ASSERT_EQ(loc.getOffset(), 5);

  loc.setOffset(0);
  ASSERT_TRUE(loc.hasOffset());
  ASSERT_EQ(loc.getOffset(), 0);

  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);

  loc.setLine();
  ASSERT_FALSE(loc.hasLine());

  loc.setLine(5);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 5);

  loc.setLine(1);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);

  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.setColumn();
  ASSERT_FALSE(loc.hasColumn());

  loc.setColumn(5);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.setColumn(1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_FALSE(loc.areMoreChars());
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_FALSE(loc.areMoreChars(1000));

  ASSERT_EQ(loc.getChar(), 0);
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_EQ(loc.getChar(1000), 0);

  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
}

TEST(Unit_Source_SourceAndLocation, Loaded_Empty) {
  Source src;

  ASSERT_FALSE(src.isLoaded());
  ASSERT_STREQ(src.getPath().c_str(), "--");

  src.loadString("");

  ASSERT_TRUE(src.isLoaded());
  ASSERT_STREQ(src.getPath().c_str(), "--");
  ASSERT_EQ(src.getCharWidth(), 1);
  ASSERT_EQ(src.getLength(), 0);

  Location loc(src);

  ASSERT_TRUE(loc.hasSource());
  ASSERT_TRUE(loc.getSource().isLoaded());
  ASSERT_STREQ(loc.getSource().getPath().c_str(), "--");

  ASSERT_FALSE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "");
  ASSERT_TRUE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "--");

  loc.setPathOverride("asdf");
  ASSERT_TRUE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "asdf");
  ASSERT_TRUE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "asdf");

  loc.setPathOverride();
  ASSERT_FALSE(loc.hasPathOverride());
  ASSERT_STREQ(loc.getPathOverride().c_str(), "");
  ASSERT_TRUE(loc.hasPath());
  ASSERT_STREQ(loc.getPath().c_str(), "--");

  ASSERT_TRUE(loc.hasOffset());
  ASSERT_EQ(loc.getOffset(), 0);

  loc.setOffset();
  ASSERT_FALSE(loc.hasOffset());

  loc.setOffset(5);
  ASSERT_TRUE(loc.hasOffset());
  ASSERT_EQ(loc.getOffset(), 5);

  loc.setOffset(0);
  ASSERT_TRUE(loc.hasOffset());
  ASSERT_EQ(loc.getOffset(), 0);

  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);

  loc.setLine();
  ASSERT_FALSE(loc.hasLine());

  loc.setLine(5);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 5);

  loc.setLine(1);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);

  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.setColumn();
  ASSERT_FALSE(loc.hasColumn());

  loc.setColumn(5);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.setColumn(1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_FALSE(loc.areMoreChars());
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_FALSE(loc.areMoreChars(1000));

  ASSERT_EQ(loc.getChar(), 0);
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_EQ(loc.getChar(1000), 0);

  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
  ASSERT_EQ(loc.eatChar(), 0);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CString_Length0_NoCopy) {
  Source src;
  src.loadCString("Hello, world.\n", 0, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CString_Length0_Copy) {
  Source src;
  src.loadCString("Hello, world.\n", 0, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CString_Length5_NoCopy) {
  Source src;
  src.loadCString("Hello, world.\n", 5, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CString_Length5_Copy) {
  Source src;
  src.loadCString("Hello, world.\n", 5, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CWString_Length0_NoCopy) {
  Source src;
  src.loadCWString(L"Hello, world.\n", 0, false);

  ASSERT_EQ(src.getCharWidth(), sizeof(wchar_t));
  ASSERT_EQ(src.getLength(), 14);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CWString_Length0_Copy) {
  Source src;
  src.loadCWString(L"Hello, world.\n", 0, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CWString_Length5_NoCopy) {
  Source src;
  src.loadCWString(L"Hello, world.\n", 5, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_CWString_Length5_Copy) {
  Source src;
  src.loadCWString(L"Hello, world.\n", 5, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C16String_Length0_NoCopy) {
  Source src;
  src.loadC16String(u"Hello, world.\n", 0, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C16String_Length0_Copy) {
  Source src;
  src.loadC16String(u"Hello, world.\n", 0, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C16String_Length5_NoCopy) {
  Source src;
  src.loadC16String(u"Hello, world.\n", 5, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C16String_Length5_Copy) {
  Source src;
  src.loadC16String(u"Hello, world.\n", 5, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C32String_Length0_NoCopy) {
  Source src;
  src.loadC32String(U"Hello, world.\n", 0, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C32String_Length0_Copy) {
  Source src;
  src.loadC32String(U"Hello, world.\n", 0, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C32String_Length5_NoCopy) {
  Source src;
  src.loadC32String(U"Hello, world.\n", 5, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_C32String_Length5_Copy) {
  Source src;
  src.loadC32String(U"Hello, world.\n", 5, true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  ASSERT_EQ(Location::distance(Location(src), loc), 5);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_String_NoCopy) {
  Source src;
  src.loadString("Hello, world.\n", false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_String_Copy) {
  Source src;
  src.loadString("Hello, world.\n", true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_WString_NoCopy) {
  std::wstring s = L"Hello, world.\n";

  Source src;
  src.loadWString(s, false);

  ASSERT_EQ(src.getCharWidth(), sizeof(wchar_t));
  ASSERT_EQ(src.getLength(), 14);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_WString_Copy) {
  Source src;
  src.loadWString(L"Hello, world.\n", true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_U16String_NoCopy) {
  std::u16string s = u"Hello, world.\n";

  Source src;
  src.loadU16String(s, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_U16String_Copy) {
  Source src;
  src.loadU16String(u"Hello, world.\n", true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_U32String_NoCopy) {
  std::u32string s = U"Hello, world.\n";

  Source src;
  src.loadU32String(s, false);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, HelloWorld_U32String_Copy) {
  Source src;
  src.loadU32String(U"Hello, world.\n", true);

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'H');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'e');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'e');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 4);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ',');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 5);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ',');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), ' ');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 6);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), ' ');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'w');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 7);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'w');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'o');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 8);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'o');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'r');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 9);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'r');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'l');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 10);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'l');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 11);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '.');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 12);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '.');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 13);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 14);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  ASSERT_EQ(Location::distance(Location(src), loc), 14);
}

TEST(Unit_Source_SourceAndLocation, Indent) {
  Source src;
  src.loadString("a\nb\n\ncd");

  Location loc(src);

  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'a');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'b');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 1);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'b');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), '\n');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 2);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), '\n');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'c');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 3);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'c');
  ASSERT_TRUE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 'd');
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 4);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 1);

  loc.eatChar();
  ASSERT_TRUE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 'd');
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 4);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 2);

  loc.eatChar();
  ASSERT_FALSE(loc.areMoreChars(0));
  ASSERT_EQ(loc.getChar(0), 0);
  ASSERT_FALSE(loc.areMoreChars(1));
  ASSERT_EQ(loc.getChar(1), 0);
  ASSERT_TRUE(loc.hasLine());
  ASSERT_EQ(loc.getLine(), 4);
  ASSERT_TRUE(loc.hasColumn());
  ASSERT_EQ(loc.getColumn(), 3);

  ASSERT_EQ(Location::distance(Location(src), loc), 7);
}
