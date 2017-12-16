#ifndef __WHISKEY_Parsing_ParserResult_HPP
#define __WHISKEY_Parsing_ParserResult_HPP

#include <whiskey/Parsing/Module.inc>

namespace whiskey {
class ParserResult {
private:
	Container<AST> ast;
	bool good;

public:
	ParserResult();
	ParserResult(Container<AST> ast);

	Ref<AST> getAST();
	CRef<AST> getAST() const;
	void setAST(Container<AST> value);

	bool isGood() const;
	void setGood(bool value);
};
}

#endif
