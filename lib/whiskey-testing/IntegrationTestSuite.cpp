#include <whiskey-testing/IntegrationTestSuite.hpp>

#include <time.h>

#include <iostream>
#include <iomanip>
#include <chrono>

namespace whiskey {
IntegrationTestSuite::IntegrationTestSuite() {}

void IntegrationTestSuite::add(IntegrationTest test) {
	tests.push_back(test);
}

bool IntegrationTestSuite::run() {
	std::cout << "Running " << tests.size() << " test" << (tests.size() == 1 ? "" : "s") << "...\n";

	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

	std::vector<IntegrationTest>::size_type passed = 0, failed = 0;
	for (IntegrationTest &i : tests) {
		if (i.run()) {
			passed++;
		} else {
			failed++;
		}
	}

	std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
	float diff = std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1>>>((end - start)).count();

	if (failed == 0) {
		std::cout << "All passed (" << std::fixed << std::setw(3) << std::setprecision(3) << diff << "s)!\n";
		return true;
	} else {
		std::cout << passed << " passed, " << failed << " failed (" << std::fixed << std::setw(3) << std::setprecision(3) << diff << "s).\n";
		return false;
	}
}
}
