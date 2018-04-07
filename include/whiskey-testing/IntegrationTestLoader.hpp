#ifndef __WHISKEY_TEST_IntegrationTestLoader_HPP
#define __WHISKEY_TEST_IntegrationTestLoader_HPP

#include <string>

namespace whiskey {
class IntegrationTest;

class IntegrationTestLoader {
public:
	bool load(const std::string &path, IntegrationTest &test);
};
}

#endif
