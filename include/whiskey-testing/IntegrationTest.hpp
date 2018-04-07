#ifndef __WHSIKEY_TEST_IntegrationTest_HPP
#define __WHSIKEY_TEST_IntegrationTest_HPP

#include <whiskey/Source/Token.hpp>

namespace whiskey {
class IntegrationTest {
private:
	std::string name;
	std::string workingPath;
	std::string sourcePath;
	bool checkTokens;
	std::vector<Token> expectedTokens;
	bool passed;

public:
	IntegrationTest();
	IntegrationTest(std::string name);

	const std::string &getName() const;
	void setName(std::string value);

	const std::string &getWorkingPath() const;
	void setWorkingPath(std::string value);

	const std::string &getSourcePath() const;
	void setSourcePath(std::string value);

	bool getCheckTokens() const;
	void setCheckTokens(bool value);

	std::vector<Token> &getExpectedTokens();
	const std::vector<Token> &getExpectedTokens() const;

	bool run();
	bool hasPassed() const;
};
}

#endif
