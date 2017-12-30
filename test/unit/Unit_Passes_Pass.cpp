#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

class Echo : public Pass {
protected:
  Node *onRunPre(Node *node) {
    return node;
  }

  Node *onRunPost(Node *node) {
    return nullptr;
  }

public:
  Echo() : Pass("echo", {"blah"}) {
  }
};

TEST(Unit_Passes_Pass, Echo) {
  Pass *pass = new Echo();

  ASSERT_STREQ(pass->getName().c_str(), "echo");
  ASSERT_EQ(pass->getDependencies().size(), 1);
  ASSERT_STREQ(pass->getDependencies()[0].c_str(), "blah");

  delete pass;
}
