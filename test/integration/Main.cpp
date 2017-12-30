#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  whiskey::LLVMGenerator::init();
  return RUN_ALL_TESTS();
}
