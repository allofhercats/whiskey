#ifndef __WHISKEY_TESTING_IntegrationTestSuite_HPP
#define __WHISKEY_TESTING_IntegrationTestSuite_HPP

#include <whiskey-testing/IntegrationTest.hpp>

namespace whiskey {
class IntegrationTestSuite {
private:
	std::vector<IntegrationTest> tests;

public:
	IntegrationTestSuite();
	IntegrationTestSuite(const IntegrationTestSuite &) = delete;

	void add(IntegrationTest test);

	bool run();
};
}

#endif
