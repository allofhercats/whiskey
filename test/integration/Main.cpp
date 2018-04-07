#include <iostream>

#include <whiskey-testing/IntegrationTest.hpp>
#include <whiskey-testing/IntegrationTestSet.hpp>
#include <whiskey-testing/IntegrationTestLoader.hpp>

using namespace whiskey;

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		std::cerr << "error: usage: " << argv[0] << " <*.yaml>\n";
		return 1;
	}

	IntegrationTestLoader loader;
	IntegrationTestSet tests;

	for (int i = 1; i < argc; i++) {
		IntegrationTest test;
		if (loader.load(argv[i], test)) {
			tests.getTests().push_back(test);
		}
	}

  return tests.run() ? 0 : 1;
}
