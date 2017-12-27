#ifndef __WHISKEY_Parsing_ParserResult_HPP
#define __WHISKEY_Parsing_ParserResult_HPP

#include <whiskey/Parsing/Module.inc>

namespace whiskey {
class ParserResult {
private:
	Node *node;
	bool good;

public:
	ParserResult();
	ParserResult(Node *node);

	Node *getNode();
	const Node *getNode() const;
	void setNode(Node *value);

	bool isGood() const;
	void setGood(bool value);
};
}

#endif
