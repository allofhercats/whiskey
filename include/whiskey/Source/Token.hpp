#ifndef __WHISKEY_Source_Token_HPP
#define __WHISKEY_Source_Token_HPP

#include <whiskey/Source/Module.inc>

#include <whiskey/Source/Source.hpp>
#include <whiskey/Source/Location.hpp>
#include <whiskey/Source/Range.hpp>

namespace whiskey {
class Token {
public:
	enum ID {
		None,
		Symbol,
		KWNot,
		KWAnd,
		KWOr,
		KWReturn,
		KWIf,
		KWElse,
		KWWhile,
		KWFor,
		KWForEach,
		KWClass,
		KWInherits,
		KWNamespace,
		KWImport,
		Int,
		Float,
		Char,
		String,
		LParen,
		RParen,
		LBracket,
		RBracket,
		LBrace,
		RBrace,
		Comma,
		Semicolon,
		Period,
		Add,
		Inc,
		AddAssign,
		Sub,
		Dec,
		SubAssign,
		Mul,
		MulAssign,
		Exp,
		ExpAssign,
		Div,
		DivAssign,
		DivInt,
		DivIntAssign,
		DivReal,
		DivRealAssign,
		Mod,
		ModAssign,
		BitNot,
		BitAnd,
		BitAndAssign,
		BitOr,
		BitOrAssign,
		BitXor,
		BitXorAssign,
		BitShL,
		BitShLAssign,
		BitShR,
		BitShRAssign,
		LT,
		LE,
		GT,
		GE,
		NE,
		EQ,
		BoolImplies,
		Assign,
		LArrow
	};

	static void printTokenIDDebug(std::ostream &os, ID value);
	static void printTokenID(std::ostream &os, ID value);

private:
	Range range;
	ID id;

public:
	static void printDebug(std::ostream &os, const Token &token);
	static void printDebug(std::ostream &os, const std::vector<Token> &tokens);

	Token(ID id = None);
	Token(Range range, ID id = None);

	bool isGood() const;

	Range &getRange();
	const Range &getRange() const;
	void setRange(Range value);

	ID getID() const;
	void setID(ID value);

	void printDebug(std::ostream &os) const;
};
}

#endif
