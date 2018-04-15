#ifndef __WHSIKEY_TEST_IntegrationTest_HPP
#define __WHSIKEY_TEST_IntegrationTest_HPP

#include <whiskey/Source/Token.hpp>
#include <whiskey/AST/Node.hpp>

namespace whiskey {
class JIT;

class IntegrationTest {
public:
	enum class SourceMode {
		Memory,
		File
	};

private:
	std::string name;
	SourceMode sourceMode;
	std::string sourceText;
	std::string sourcePath;
	bool checkTokens;
	bool reLexTokens;
	std::vector<Token> expectedTokens;
	bool checkAST;
	Node expectedAST;
	std::function<void(JIT &)> executionTest;

	bool compareTokenVectors(const std::vector<Token> &expectedTokens, const std::vector<Token> &actualTokens, bool isReLex);

public:
	IntegrationTest(std::string name);

	std::string &getName();
	const std::string &getName() const;
	void setName(std::string value);

	SourceMode getSourceMode() const;
	void setSourceMode(SourceMode value);

	std::string &getSourceText();
	const std::string &getSourceText() const;
	void setSourceText(std::string value);

	std::string &getSourcePath();
	const std::string &getSourcePath() const;
	void setSourcePath(std::string value);

	bool getCheckTokens() const;
	void setCheckTokens(bool value);

	bool getReLexTokens() const;
	void setReLexTokens(bool value);

	std::vector<Token> &getExpectedTokens();
	const std::vector<Token> &getExpectedTokens() const;
	void setExpectedTokens(std::vector<Token> value);

	bool getCheckAST() const;
	void setCheckAST(bool value);

	Node &getExpectedAST();
	const Node &getExpectedAST() const;
	void setExpectedAST(Node value);

	const std::function<void(JIT &)> &getExecutionTest() const;
	void setExecutionTest(std::function<void(JIT &)> value);

	bool run();
};
}

#endif
