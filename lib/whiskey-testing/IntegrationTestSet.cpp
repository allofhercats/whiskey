#include <whiskey-testing/IntegrationTestSet.hpp>

#include <iostream>

namespace whiskey {
IntegrationTestSet::IntegrationTestSet() : nPassed(0), nFailed(0) {}

std::vector<IntegrationTest> &IntegrationTestSet::getTests() {
	return tests;
}

const std::vector<IntegrationTest> &IntegrationTestSet::getTests() const {
	return tests;
}

bool IntegrationTestSet::run() {
	nPassed = nFailed = 0;

	std::cout << "Running " << tests.size() << " test" << (tests.size() == 1 ? "" : "s") << "...\n";

	for (IntegrationTest &i : tests) {
		if (i.run()) {
			nPassed++;
		} else {
			nFailed++;
		}
	}

	if (hasPassed()) {
		std::cout << "All passed!\n";
		return true;
	} else {
		std::cout << "Passed " << nPassed << ", failed " << nFailed << ".\n";
		return false;
	}
}

bool IntegrationTestSet::hasPassed() const {
	return nFailed == 0;
}

std::vector<IntegrationTest>::size_type IntegrationTestSet::getNPassed() const {
	return nPassed;
}

std::vector<IntegrationTest>::size_type IntegrationTestSet::getNFailed() const {
	return nFailed;
}
}
