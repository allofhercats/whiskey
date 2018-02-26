#ifndef __WHISKEY_Parsing_ParserRule_HPP
#define __WHISKEY_Parsing_ParserRule_HPP

#include <string>
#include <memory>
#include <vector>

namespace whiskey {
class ParserResult;
class ParserGrammar;
class ParserContext;
class MessageContext;

class ParserRule {
private:
	std::string name;

protected:
	virtual ParserResult onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const = 0;

public:
	ParserRule(std::string name);

	template<class T>
  T &as();
  template<class T>
  const T &as() const;

	std::string &getName();
	const std::string &getName() const;
	void setName(std::string value);

	ParserResult parse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const;
};

typedef std::vector<std::unique_ptr<ParserRule>>::size_type ParserRuleID;
}

#include <whiskey/Parsing/ParserRule.tpp>

#endif
