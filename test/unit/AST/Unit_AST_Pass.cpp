#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Pass.hpp>

using namespace whiskey;

class Echo : public Pass {
protected:
  PassResult onRunPre(Node &node, MessageContext &msgs) {
    return PassResult::Good;
  }

  PassResult onRunPost(Node &node, MessageContext &msgs) {
    return PassResult::Good;
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
