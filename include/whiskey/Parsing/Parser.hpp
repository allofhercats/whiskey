#ifndef __WHISKEY_Parsing_Parser_HPP
#define __WHISKEY_Parsing_Parser_HPP

#include <memory>

#include <whiskey/Parsing/ParserGrammar.hpp>

namespace whiskey {
class Node;

class Parser {
private:
	ParserGrammar grammar;

public:
	static void createGrammar(ParserGrammar &grammar);

	Parser();

	bool isGrammarInitted() const;
	void initGrammar();

	Node parse(ParserContext &ctx, MessageContext &msgs) const;
};
} // namespace whiskey

#endif
