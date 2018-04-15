#include "Integration.hpp"

#include <whiskey/CodeGen/LLVMJIT.hpp>

#include <whiskey-testing/IntegrationTestSuite.hpp>

using namespace whiskey;

IntegrationTestSuite suite;

int main(int argc, char *argv[]) {
	LLVMJIT::init();

	initSimple();
  return suite.run() ? 0 : 1;
}
