#ifndef __WHISKEY_TEST_IntegrationTestSet_HPP
#define __WHISKEY_TEST_IntegrationTestSet_HPP

#include <whiskey-testing/IntegrationTest.hpp>

namespace whiskey {
class IntegrationTestSet {
private:
	std::vector<IntegrationTest> tests;
	std::vector<IntegrationTest>::size_type nPassed;
	std::vector<IntegrationTest>::size_type nFailed;

public:
	IntegrationTestSet();

	std::vector<IntegrationTest> &getTests();
	const std::vector<IntegrationTest> &getTests() const;

	bool run();
	bool hasPassed() const;
	std::vector<IntegrationTest>::size_type getNPassed() const;
	std::vector<IntegrationTest>::size_type getNFailed() const;
};
}

#endif
