#include <whiskey/Lexing/Lexer.hpp>

#include <string.h>

#include <iostream>

#include <whiskey/Core/Literals.hpp>
#include <whiskey/Core/Verbose.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Lexing/LexerContext.hpp>

namespace whiskey {
const char *Lexer::getStateName(Lexer::State state) {
	switch (state) {
		case Start: return "Start";
		case Comment: return "Comment";
		case CommentLine: return "CommentLine";
		case CommentBlock: return "CommentBlock";
		case Symbol: return "Symbol";
		case SymbolPrimes: return "SymbolPrimes";
		case Int: return "Int";
		case Real: return "Real";
		case Char: return "Char";
		case String: return "String";
		case Period: return "Period";
		case Add: return "Add";
		case Sub: return "Sub";
		case Mul: return "Mul";
		case Exp: return "Exp";
		case Div: return "Div";
		case DivInt: return "DivInt";
		case DivReal: return "DivReal";
		case Mod: return "Mod";
		case BitAnd: return "BitAnd";
		case BitOr: return "BitOr";
		case BitXor: return "BitXor";
		case LT: return "LT";
		case BitShL: return "BitShL";
		case GT: return "GT";
		case BitShR: return "BitShR";
		case Assign: return "Assign";
		case NE: return "NE";
	}
}

void Lexer::emitSymbol(LexerContext &ctx) {
	std::string buffer = ctx.getBuffer();
	if (buffer == "bool") {
		ctx.emit(TokenID::KWBool);
	} else if (buffer == "int8") {
		ctx.emit(TokenID::KWInt8);
	} else if (buffer == "int16") {
		ctx.emit(TokenID::KWInt16);
	} else if (buffer == "int32") {
		ctx.emit(TokenID::KWInt32);
	} else if (buffer == "int64") {
		ctx.emit(TokenID::KWInt64);
	} else if (buffer == "uint8") {
		ctx.emit(TokenID::KWUInt8);
	} else if (buffer == "uint16") {
		ctx.emit(TokenID::KWUInt16);
	} else if (buffer == "uint32") {
		ctx.emit(TokenID::KWUInt32);
	} else if (buffer == "uint64") {
		ctx.emit(TokenID::KWUInt64);
	} else if (buffer == "float32") {
		ctx.emit(TokenID::KWFloat32);
	} else if (buffer == "float64") {
		ctx.emit(TokenID::KWFloat64);
	} else if (buffer == "real") {
		ctx.emit(TokenID::KWReal);
	} else if (buffer == "true") {
		ctx.emit(TokenID::KWTrue);
	} else if (buffer == "false") {
		ctx.emit(TokenID::KWFalse);
	} else if (buffer == "not") {
		ctx.emit(TokenID::KWNot);
	} else if (buffer == "and") {
		ctx.emit(TokenID::KWAnd);
	} else if (buffer == "or") {
		ctx.emit(TokenID::KWOr);
	} else if (buffer == "return") {
		ctx.emit(TokenID::KWReturn);
	} else if (buffer == "continue") {
		ctx.emit(TokenID::KWContinue);
	} else if (buffer == "break") {
		ctx.emit(TokenID::KWBreak);
	} else if (buffer == "if") {
		ctx.emit(TokenID::KWIf);
	} else if (buffer == "else") {
		ctx.emit(TokenID::KWElse);
	} else if (buffer == "while") {
		ctx.emit(TokenID::KWWhile);
	} else if (buffer == "for") {
		ctx.emit(TokenID::KWFor);
	} else if (buffer == "foreach") {
		ctx.emit(TokenID::KWForEach);
	} else if (buffer == "class") {
		ctx.emit(TokenID::KWClass);
	} else if (buffer == "inherits") {
		ctx.emit(TokenID::KWInherits);
	} else if (buffer == "namespace") {
		ctx.emit(TokenID::KWNamespace);
	} else if (buffer == "import") {
		ctx.emit(TokenID::KWImport);
	} else {
		ctx.emit(TokenID::Symbol);
	}
}

void Lexer::lexOne(LexerContext &ctx, MessageContext &msg) {
	switch (state) {
		case Start:
			if (chr >= 'a' && chr <= 'z') {
				ctx.buffer(chr);
				state = Symbol;
				handled = true;
			} else if (chr >= 'A' && chr <= 'Z') {
				ctx.buffer(chr);
				state = Symbol;
				handled = true;
			} else if (static_cast<uint8_t>(chr) >= 0x80) {
				ctx.buffer(chr);
				state = Symbol;
				handled = true;
			} else if (chr == '_') {
				ctx.buffer(chr);
				state = Symbol;
				handled = true;
			} else if (chr >= '0' && chr <= '9') {
				ctx.buffer(chr);
				state = Int;
				handled = true;
			} else if (chr == '\'') {
				ctx.buffer(chr);
				state = Char;
				handled = true;
			} else if (chr == '\"') {
				ctx.buffer(chr);
				state = String;
				handled = true;
			} else if (chr == ' ' || chr == '\t' || chr == '\n') {
				ctx.skip();
				handled = true;
			} else if (chr == '#') {
				state = Comment;
				handled = true;
			} else if (chr == '(') {
				ctx.emit(TokenID::LParen);
				handled = true;
			} else if (chr == ')') {
				ctx.emit(TokenID::RParen);
				handled = true;
			} else if (chr == '[') {
				ctx.emit(TokenID::LBracket);
				handled = true;
			} else if (chr == ']') {
				ctx.emit(TokenID::RBracket);
				handled = true;
			} else if (chr == '{') {
				ctx.emit(TokenID::LBrace);
				handled = true;
			} else if (chr == '}') {
				ctx.emit(TokenID::RBrace);
				handled = true;
			} else if (chr == ',') {
				ctx.emit(TokenID::Comma);
				handled = true;
			} else if (chr == ';') {
				ctx.emit(TokenID::Semicolon);
				handled = true;
			} else if (chr == '.') {
				state = Period;
				handled = true;
			} else if (chr == '+') {
				state = Add;
				handled = true;
			} else if (chr == '-') {
				state = Sub;
				handled = true;
			} else if (chr == '*') {
				state = Mul;
				handled = true;
			} else if (chr == '/') {
				state = Div;
				handled = true;
			} else if (chr == '%') {
				state = Mod;
				handled = true;
			} else if (chr == '~') {
				ctx.emit(TokenID::BitNot);
				handled = true;
			} else if (chr == '&') {
				state = BitAnd;
				handled = true;
			} else if (chr == '|') {
				state = BitOr;
				handled = true;
			} else if (chr == '^') {
				state = BitXor;
				handled = true;
			} else if (chr == '<') {
				state = LT;
				handled = true;
			} else if (chr == '>') {
				state = GT;
				handled = true;
			} else if (chr == '=') {
				state = Assign;
				handled = true;
			} else if (chr == '!') {
				state = NE;
				handled = true;
			} else if (chr == 0) {
				running = false;
				ctx.skip();
			} else {
				msg.describe() << "Use of illegal character ";
				printLiteralChar(msg.describe(), static_cast<Char32>(chr));
				msg.describe() << ".";
				msg.emit(ctx.createErrorToken(), Message::Error);
				handled = true;
				ctx.skip();
			}
			break;
		case Comment:
			if (chr == '{') {
				state = CommentBlock;
				commentBlockLevel = 1;
				handled = true;
			} else {
				state = CommentLine;
			}
			break;
		case CommentLine:
			if (chr == '\n' || chr == 0) {
				ctx.skip();
				state = Start;
				handled = true;
			} else {
				handled = true;
			}
			break;
		case CommentBlock:
			if (last[1] == '#' && chr == '{') {
				commentBlockLevel++;
				handled = true;
			} else if (last[1] == '}' && chr == '#') {
				commentBlockLevel--;
				if (commentBlockLevel <= 0) {
					ctx.skip();
					state = Start;
					handled = true;
				} else {
					handled = true;
				}
			} else if (chr == 0) {
				msg.describe() << "#{ expects closing }#.";
				msg.emit(ctx.createErrorToken(), Message::Error);

				ctx.skip();
				state = Start;
			} else {
				handled = true;
			}
			break;
		case Symbol:
			if (chr >= 'a' && chr <= 'z') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr >= 'A' && chr <= 'Z') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr >= '0' && chr <= '9') {
				ctx.buffer(chr);
				handled = true;
			} else if (static_cast<uint8_t>(chr) >= 0x80) {
				ctx.buffer(chr);
				handled = true;
			} else if (chr == '_') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr == '\'') {
				state = SymbolPrimes;
			} else {
				emitSymbol(ctx);
				state = Start;
			}
			break;
		case SymbolPrimes:
			if (chr == '\'') {
				ctx.buffer(chr);
				handled = true;
			} else {
				emitSymbol(ctx);
				state = Start;
			}
			break;
		case Int:
			if (chr >= '0' && chr <= '9') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr >= 'a' && chr <= 'z') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr >= 'A' && chr <= 'Z') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr == '.') {
				ctx.buffer(chr);
				state = Real;
				handled = true;
			} else {
				ctx.emit(TokenID::Int);
				state = Start;
			}
			break;
		case Real:
			if (chr >= '0' && chr <= '9') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr >= 'a' && chr <= 'z') {
				ctx.buffer(chr);
				handled = true;
			} else if (chr >= 'A' && chr <= 'Z') {
				ctx.buffer(chr);
				handled = true;
			} else {
				ctx.emit(TokenID::Real);
				state = Start;
			}
			break;
		case Char:
			if (chr == '\'' && (last[0] == '\\' || last[1] != '\\')) {
				ctx.buffer(chr);
				ctx.emit(TokenID::Char);
				state = Start;
				handled = true;
			} else if (chr == 0) {
				msg.describe() << "\' expects closing \'.";
				msg.emit(ctx.createErrorToken(), Message::Error);
				running = false;
			} else {
				ctx.buffer(chr);
				handled = true;
			}
			break;
		case String:
			if (chr == '\"' && (last[0] == '\\' || last[1] != '\\')) {
				ctx.buffer(chr);
				ctx.emit(TokenID::String);
				state = Start;
				handled = true;
			} else if (chr == 0) {
				msg.describe() << "\" expects closing \".";
				msg.emit(ctx.createErrorToken(), Message::Error);
				running = false;
			} else {
				ctx.buffer(chr);
				handled = true;
			}
			break;
		case Period:
			if (chr >= '0' && chr <= '9') {
				ctx.buffer('.');
				state = Real;
			} else {
				ctx.emit(TokenID::Period);
				state = Start;
			}
			break;
		case Add:
			if (chr == '+') {
				ctx.emit(TokenID::Inc);
				state = Start;
				handled = true;
			} else if (chr == '=') {
				ctx.emit(TokenID::AddAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::Add);
				state = Start;
			}
			break;
		case Sub:
			if (chr == '-') {
				ctx.emit(TokenID::Dec);
				state = Start;
				handled = true;
			} else if (chr == '=') {
				ctx.emit(TokenID::SubAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::Sub);
				state = Start;
			}
			break;
		case Mul:
			if (chr == '*') {
				state = Exp;
				handled = true;
			} else if (chr == '=') {
				ctx.emit(TokenID::MulAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::Mul);
				state = Start;
			}
			break;
		case Exp:
			if (chr == '=') {
				ctx.emit(TokenID::ExpAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::Exp);
				state = Start;
			}
			break;
		case Div:
			if (chr == '/') {
				state = DivInt;
				handled = true;
			} else if (chr == '.') {
				state = DivReal;
				handled = true;
			} else if (chr == '=') {
				ctx.emit(TokenID::DivAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::Div);
				state = Start;
			}
			break;
		case DivInt:
			if (chr == '=') {
				ctx.emit(TokenID::DivIntAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::DivInt);
				state = Start;
			}
			break;
		case DivReal:
			if (chr == '=') {
				ctx.emit(TokenID::DivRealAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::DivReal);
				state = Start;
			}
			break;
		case Mod:
			if (chr == '=') {
				ctx.emit(TokenID::ModAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::Mod);
				state = Start;
			}
			break;
		case BitAnd:
			if (chr == '=') {
				ctx.emit(TokenID::BitAndAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::BitAnd);
				state = Start;
			}
			break;
		case BitOr:
			if (chr == '=') {
				ctx.emit(TokenID::BitOrAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::BitOr);
				state = Start;
			}
			break;
		case BitXor:
			if (chr == '=') {
				ctx.emit(TokenID::BitXorAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::BitXor);
				state = Start;
			}
			break;
		case LT:
			if (chr == '<') {
				state = BitShL;
				handled = true;
			} else if (chr == '=') {
				ctx.emit(TokenID::LE);
				state = Start;
				handled = true;
			} else if (chr == '-') {
				ctx.emit(TokenID::LArrow);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::LT);
				state = Start;
			}
			break;
		case BitShL:
			if (chr == '=') {
				ctx.emit(TokenID::BitShLAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::BitShL);
				state = Start;
			}
			break;
		case GT:
			if (chr == '>') {
				state = BitShR;
				handled = true;
			} else if (chr == '=') {
				ctx.emit(TokenID::GE);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::GT);
				state = Start;
			}
			break;
		case BitShR:
			if (chr == '=') {
				ctx.emit(TokenID::BitShRAssign);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::BitShR);
				state = Start;
			}
			break;
		case Assign:
			if (chr == '=') {
				ctx.emit(TokenID::EQ);
				state = Start;
				handled = true;
			} else if (chr == '>') {
				ctx.emit(TokenID::BoolImplies);
				state = Start;
				handled = true;
			} else {
				ctx.emit(TokenID::Assign);
				state = Start;
			}
			break;
		case NE:
			if (chr == '=') {
				ctx.emit(TokenID::NE);
				state = Start;
				handled = true;
			} else {
				msg.describe() << "Use 'not' operator for boolean not.";
				msg.emitChild(ctx.createErrorToken(), Message::Note);

				msg.describe() << "'!' can only be used in '!=' operator, not on its own.";
				msg.emit(ctx.createErrorToken(), Message::Error);

				ctx.skip();
				state = Start;
				handled = true;
			}
			break;
	}
}

Lexer::Lexer() {}

void Lexer::lex(LexerContext &ctx, MessageContext &msg) {
	state = Start;
	chr = 0;
	memset(last, 0, sizeof(last));
	handled = true;
	running = true;

	while (running) {
		if (handled) {
			chr = ctx.eat();

			#ifdef W_ENABLE_VERBOSE
			if (isprint(chr)) {
				W_VERBOSE("read '" << chr << "' (" << std::hex << static_cast<int>(chr) << ")");
			} else {
				W_VERBOSE("read (" << std::hex << static_cast<int>(chr) << ")");
			}
			#endif

			handled = false;
		}

		#ifdef W_ENABLE_VERBOSE
		State stateBefore = state;
		std::vector<Token>::size_type nTokensBefore = ctx.getNTokens();
		#endif

		lexOne(ctx, msg);

		#ifdef W_ENABLE_VERBOSE
		if (state != stateBefore) {
			W_VERBOSE("state to " << getStateName(state));
		}

		if (ctx.getNTokens() > nTokensBefore) {
			W_VERBOSE("emit " << ctx.getLastToken());
		}
		#endif

		for (int i = 0; i < W_LEXER_SAVE_LAST-1; i++) {
			last[i] = last[i+1];
		}

		last[W_LEXER_SAVE_LAST-1] = chr;
	}
}
}
