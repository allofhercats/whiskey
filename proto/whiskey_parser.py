import enum

import token
import ast
import base_parser
import whiskey_lexer

@enum.unique
class ASTID(enum.Enum):
	SYMBOL = enum.auto()
	DECORATOR = enum.auto()
	DECORATED = enum.auto()
	ACCESS = enum.auto()
	TEMPLATE_EVAL = enum.auto()
	TEMPLATE_DECL_ARG_TYPE = enum.auto()
	TEMPLATE_DECL = enum.auto()
	EXPR_LITERAL_BOOL = enum.auto()
	EXPR_LITERAL_INT = enum.auto()
	EXPR_LITERAL_FLOAT = enum.auto()
	EXPR_LITERAL_CHAR = enum.auto()
	EXPR_LITERAL_STRING = enum.auto()
	EXPR_TEMPLATE = enum.auto()
	EXPR_CALL = enum.auto()
	EXPR_ADD = enum.auto()
	EXPR_ADD_ASSIGN = enum.auto()
	EXPR_INC_PRE = enum.auto()
	EXPR_INC_POST = enum.auto()
	EXPR_NEGATE = enum.auto()
	EXPR_SUB = enum.auto()
	EXPR_SUB_ASSIGN = enum.auto()
	EXPR_DEC_PRE = enum.auto()
	EXPR_DEC_POST = enum.auto()
	EXPR_MUL = enum.auto()
	EXPR_MUL_ASSIGN = enum.auto()
	EXPR_DIV = enum.auto()
	EXPR_DIV_ASSIGN = enum.auto()
	EXPR_DIV_INT = enum.auto()
	EXPR_DIV_INT_ASSIGN = enum.auto()
	EXPR_DIV_REAL = enum.auto()
	EXPR_DIV_REAL_ASSIGN = enum.auto()
	EXPR_EXP = enum.auto()
	EXPR_EXP_ASSIGN = enum.auto()
	EXPR_MOD = enum.auto()
	EXPR_MOD_ASSIGN = enum.auto()
	EXPR_BIT_SHR = enum.auto()
	EXPR_BIT_SHR_ASSIGN = enum.auto()
	EXPR_BIT_SHL = enum.auto()
	EXPR_BIT_SHL_ASSIGN = enum.auto()
	EXPR_BIT_NOT = enum.auto()
	EXPR_BIT_AND = enum.auto()
	EXPR_BIT_AND_ASSIGN = enum.auto()
	EXPR_BIT_OR = enum.auto()
	EXPR_BIT_OR_ASSIGN = enum.auto()
	EXPR_BIT_XOR = enum.auto()
	EXPR_BIT_XOR_ASSIGN = enum.auto()
	EXPR_LT = enum.auto()
	EXPR_LE = enum.auto()
	EXPR_GT = enum.auto()
	EXPR_GE = enum.auto()
	EXPR_NE = enum.auto()
	EXPR_EQ = enum.auto()
	EXPR_BOOL_NOT = enum.auto()
	EXPR_BOOL_AND = enum.auto()
	EXPR_BOOL_IMPLIES = enum.auto()
	EXPR_BOOL_OR = enum.auto()
	EXPR_ASSIGN = enum.auto()
	TYPE_BOOL = enum.auto()
	TYPE_INT = enum.auto()
	TYPE_INT8 = enum.auto()
	TYPE_INT16 = enum.auto()
	TYPE_INT32 = enum.auto()
	TYPE_INT64 = enum.auto()
	TYPE_BIGINT = enum.auto()
	TYPE_UINT = enum.auto()
	TYPE_UINT8 = enum.auto()
	TYPE_UINT16 = enum.auto()
	TYPE_UINT32 = enum.auto()
	TYPE_UINT64 = enum.auto()
	TYPE_BIGUINT = enum.auto()
	TYPE_CHAR = enum.auto()
	TYPE_CHAR8 = enum.auto()
	TYPE_CHAR16 = enum.auto()
	TYPE_CHAR32 = enum.auto()
	TYPE_FLOAT = enum.auto()
	TYPE_FLOAT32 = enum.auto()
	TYPE_FLOAT64 = enum.auto()
	TYPE_RATIO = enum.auto()
	TYPE_RATIO8 = enum.auto()
	TYPE_RATIO16 = enum.auto()
	TYPE_RATIO32 = enum.auto()
	TYPE_RATIO64 = enum.auto()
	TYPE_BIGRATIO = enum.auto()
	TYPE_REAL = enum.auto()
	TYPE_BIGREAL = enum.auto()
	STMT_RETURN = enum.auto()
	STMT_THROW = enum.auto()
	STMT_IF = enum.auto()
	STMT_WHILE = enum.auto()
	STMT_FOR = enum.auto()
	STMT_FOREACH = enum.auto()
	STMT_TRY = enum.auto()
	STMT_CATCH = enum.auto()
	STMT_BLOCK = enum.auto()
	DECL_VAR = enum.auto()
	DECL_FUNC = enum.auto()
	DECL_CLASS = enum.auto()
	DECL_ENUM = enum.auto()
	DECL_NAMESPACE = enum.auto()
	TOPLEVEL_IMPORT = enum.auto()
	TOPLEVEL_IMPORT_USING = enum.auto()
	TOPLEVEL_USING = enum.auto()
	PAGE = enum.auto()

class WhiskeyParser(base_parser.BaseParser):
	@staticmethod
	def rule_expr_symbol(parser):
		tok = parser.try_token(whiskey_lexer.TokenID.SYMBOL)
		if tok is None:
			return base_parser.ParserResult(None, False)
		else:
			return base_parser.ParserResult(
				ast.AST(
					tok,
					ASTID.SYMBOL,
					name = tok.text
				), True)

	@staticmethod
	def rule_expr_literal_bool(parser):
		tok = parser.get_token()
		if tok.tid == whiskey_lexer.TokenID.KW_TRUE:
			parser.eat_token()
			return base_parser.ParserResult(
				ast.AST(
					tok,
					ASTID.EXPR_LITERAL_BOOL,
					value = True
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_FALSE:
			parser.eat_token()
			return base_parser.ParserResult(
				ast.AST(
					tok,
					ASTID.EXPR_LITERAL_BOOL,
					value = False
				), True)
		else:
			return base_parser.ParserResult(None, False)

	@staticmethod
	def rule_expr_literal_int(parser):
		tok = parser.try_token(whiskey_lexer.TokenID.LITERAL_INT)
		if tok is None:
			return base_parser.ParserResult(None, False)
		else:
			return base_parser.ParserResult(
				ast.AST(
					tok,
					ASTID.EXPR_LITERAL_INT,
					value = int(tok.text)
				), True)

	@staticmethod
	def rule_expr_literal_float(parser):
		tok = parser.try_token(whiskey_lexer.TokenID.LITERAL_FLOAT)
		if tok is None:
			return base_parser.ParserResult(None, False)
		else:
			return base_parser.ParserResult(
				ast.AST(
					tok,
					ASTID.EXPR_LITERAL_FLOAT,
					value = float(tok.text)
				), True)

	@staticmethod
	def rule_expr_literal_char(parser):
		tok = parser.try_token(whiskey_lexer.TokenID.LITERAL_CHAR)
		if tok is None:
			return base_parser.ParserResult(None, False)
		else:
			try:
				return base_parser.ParserResult(
					ast.AST(
						tok,
						ASTID.EXPR_LITERAL_CHAR,
						value = bytes(tok.text[1:-1], "utf-8").decode("unicode_escape")[0]
					), True)
			except IndexError:
				raise base_parser.ParserError("char literals cannot be 0 length")

	@staticmethod
	def rule_expr_literal_string(parser):
		tok = parser.try_token(whiskey_lexer.TokenID.LITERAL_STRING)
		if tok is None:
			return base_parser.ParserResult(None, False)
		else:
			return base_parser.ParserResult(
				ast.AST(
					tok,
					ASTID.EXPR_LITERAL_STRING,
					value = bytes(tok.text[1:-1], "utf-8").decode("unicode_escape")
				), True)

	@staticmethod
	def rule_expr_group(parser):
		return parser.parse_bound(WhiskeyParser.rule_expr, whiskey_lexer.TokenID.LPAREN, whiskey_lexer.TokenID.RPAREN)

	@staticmethod
	def rule_expr_term(parser):
		return parser.try_parse_anyof(
			WhiskeyParser.rule_expr_symbol,
			WhiskeyParser.rule_expr_literal_bool,
			WhiskeyParser.rule_expr_literal_int,
			WhiskeyParser.rule_expr_literal_float,
			WhiskeyParser.rule_expr_literal_char,
			WhiskeyParser.rule_expr_literal_string,
			WhiskeyParser.rule_expr_group
		)

	@staticmethod
	def rule_expr_templated(parser):
		templatee = parser.try_parse(WhiskeyParser.rule_expr_term)
		if not templatee.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			return templatee

		tok = parser.get_token()
		if tok.tid == whiskey_lexer.TokenID.LT:
			parser.eat_token()

			args = []

			while parser.more_tokens():
				arg = parser.expect_parse(WhiskeyParser.rule_expr_term)
				if not arg.keep:
					return base_parser.ParserResult(None, False)

				if not parser.more_tokens():
					raise base_parser.ParserError("unexpected end of stream")

				args.append(arg.ast)

				tok = parser.get_token()
				if tok.tid == whiskey_lexer.TokenID.COMMA:
					parser.eat_token()
					continue
				elif tok.tid == whiskey_lexer.TokenID.BIT_SHR_ASSIGN:
					parser.eat_token()
					parser.inject_token(token.Token("--", 0, 0, -1, whiskey_lexer.TokenID.GE, ">="))
					break
				elif tok.tid == whiskey_lexer.TokenID.BIT_SHR:
					parser.eat_token()
					parser.inject_token(token.Token("--", 0, 0, -1, whiskey_lexer.TokenID.GT, ">"))
					break
				elif tok.tid == whiskey_lexer.TokenID.GE:
					parser.eat_token()
					parser.inject_token(token.Token("--", 0, 0, -1, whiskey_lexer.TokenID.ASSIGN, "="))
					break
				elif tok.tid == whiskey_lexer.TokenID.GT:
					parser.eat_token()
					break
				elif tok.tid == whiskey_lexer.TokenID.BIT_SHR:
					parser.eat_token()
					continue

			return base_parser.ParserResult(ast.AST(
					templatee.ast.token,
					ASTID.EXPR_TEMPLATE,
					templatee = templatee.ast,
					args = args
				), True)
		else:
			return templatee

	@staticmethod
	def rule_expr_access(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_templated,
				WhiskeyParser.rule_expr_access,
				[
					(whiskey_lexer.TokenID.PERIOD, ASTID.ACCESS)
				]
			)

	@staticmethod
	def rule_expr_call(parser):
		callee = parser.try_parse(WhiskeyParser.rule_expr_access)
		if not callee.keep:
			return callee

		if parser.more_tokens() and parser.get_token().tid == whiskey_lexer.TokenID.LPAREN:
			args = parser.parse_bound_list(WhiskeyParser.rule_expr, whiskey_lexer.TokenID.COMMA, whiskey_lexer.TokenID.LPAREN, whiskey_lexer.TokenID.RPAREN)
			if args.keep:
				return base_parser.ParserResult(ast.AST(
					callee.ast.token,
					ASTID.EXPR_CALL,
					callee = callee.ast,
					args = args.ast
					), True)
			else:
				base_parser.ParserResult(None, False)
		else:
			return callee

	@staticmethod
	def rule_expr_call_access(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_call,
				WhiskeyParser.rule_expr_call_access,
				[
					(whiskey_lexer.TokenID.PERIOD, ASTID.ACCESS)
				]
			)

	@staticmethod
	def rule_expr_unary_right(parser):
		return parser.parse_unary_right(
				WhiskeyParser.rule_expr_unary_right,
				WhiskeyParser.rule_expr_call_access,
				[
					(whiskey_lexer.TokenID.INC, ASTID.EXPR_INC_PRE),
					(whiskey_lexer.TokenID.DEC, ASTID.EXPR_DEC_PRE),
					(whiskey_lexer.TokenID.SUB, ASTID.EXPR_NEGATE)
				]
			)

	@staticmethod
	def rule_expr_unary_left(parser):
		return parser.parse_unary_left(
				WhiskeyParser.rule_expr_unary_right,
				[
					(whiskey_lexer.TokenID.INC, ASTID.EXPR_INC_POST),
					(whiskey_lexer.TokenID.DEC, ASTID.EXPR_DEC_POST)
				]
			)

	@staticmethod
	def rule_expr_exp(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_unary_left,
				WhiskeyParser.rule_expr_exp,
				[
					(whiskey_lexer.TokenID.EXP, ASTID.EXPR_EXP)
				]
			)

	@staticmethod
	def rule_expr_mul(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_exp,
				WhiskeyParser.rule_expr_mul,
				[
					(whiskey_lexer.TokenID.MUL, ASTID.EXPR_MUL),
					(whiskey_lexer.TokenID.DIV, ASTID.EXPR_DIV),
					(whiskey_lexer.TokenID.DIV_INT, ASTID.EXPR_DIV_INT),
					(whiskey_lexer.TokenID.DIV_REAL, ASTID.EXPR_DIV_REAL)
				]
			)

	@staticmethod
	def rule_expr_add(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_mul,
				WhiskeyParser.rule_expr_add,
				[
					(whiskey_lexer.TokenID.ADD, ASTID.EXPR_ADD),
					(whiskey_lexer.TokenID.SUB, ASTID.EXPR_SUB)
				]
			)

	@staticmethod
	def rule_expr_mod(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_add,
				WhiskeyParser.rule_expr_mod,
				[
					(whiskey_lexer.TokenID.MOD, ASTID.EXPR_MOD)
				]
			)

	@staticmethod
	def rule_expr_bitshr(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_mod,
				WhiskeyParser.rule_expr_bitshr,
				[
					(whiskey_lexer.TokenID.BIT_SHR, ASTID.EXPR_BIT_SHR)
				]
			)

	@staticmethod
	def rule_expr_bitshl(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bitshr,
				WhiskeyParser.rule_expr_bitshl,
				[
					(whiskey_lexer.TokenID.BIT_SHL, ASTID.EXPR_BIT_SHL)
				]
			)

	@staticmethod
	def rule_expr_bitnot(parser):
		return parser.parse_unary_right(
				WhiskeyParser.rule_expr_bitnot,
				WhiskeyParser.rule_expr_bitshl,
				[
					(whiskey_lexer.TokenID.BIT_NOT, ASTID.EXPR_BIT_NOT)
				]
			)

	@staticmethod
	def rule_expr_bitand(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bitnot,
				WhiskeyParser.rule_expr_bitand,
				[
					(whiskey_lexer.TokenID.BIT_AND, ASTID.EXPR_BIT_AND)
				]
			)

	@staticmethod
	def rule_expr_bitor(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bitand,
				WhiskeyParser.rule_expr_bitor,
				[
					(whiskey_lexer.TokenID.BIT_OR, ASTID.EXPR_BIT_OR),
					(whiskey_lexer.TokenID.BIT_XOR, ASTID.EXPR_BIT_XOR)
				]
			)

	@staticmethod
	def rule_expr_cmp(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bitor,
				WhiskeyParser.rule_expr_cmp,
				[
					(whiskey_lexer.TokenID.LT, ASTID.EXPR_LT),
					(whiskey_lexer.TokenID.LE, ASTID.EXPR_LE),
					(whiskey_lexer.TokenID.GT, ASTID.EXPR_GT),
					(whiskey_lexer.TokenID.GE, ASTID.EXPR_GE),
					(whiskey_lexer.TokenID.NE, ASTID.EXPR_NE),
					(whiskey_lexer.TokenID.EQ, ASTID.EXPR_EQ)
				]
			)

	@staticmethod
	def rule_expr_bool_not(parser):
		return parser.parse_unary_right(
				WhiskeyParser.rule_expr_bool_not,
				WhiskeyParser.rule_expr_cmp,
				[
					(whiskey_lexer.TokenID.KW_NOT, ASTID.EXPR_BOOL_NOT)
				]
			)

	@staticmethod
	def rule_expr_bool_and(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bool_not,
				WhiskeyParser.rule_expr_bool_and,
				[
					(whiskey_lexer.TokenID.KW_AND, ASTID.EXPR_BOOL_AND)
				]
			)

	@staticmethod
	def rule_expr_bool_implies(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bool_and,
				WhiskeyParser.rule_expr_bool_implies,
				[
					(whiskey_lexer.TokenID.BOOL_IMPLIES, ASTID.EXPR_BOOL_IMPLIES)
				]
			)

	@staticmethod
	def rule_expr_bool_or(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bool_implies,
				WhiskeyParser.rule_expr_bool_or,
				[
					(whiskey_lexer.TokenID.KW_OR, ASTID.EXPR_BOOL_OR)
				]
			)

	@staticmethod
	def rule_expr_assign(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_expr_bool_or,
				WhiskeyParser.rule_expr_assign,
				[
					(whiskey_lexer.TokenID.ADD_ASSIGN, ASTID.EXPR_ADD_ASSIGN),
					(whiskey_lexer.TokenID.SUB_ASSIGN, ASTID.EXPR_SUB_ASSIGN),
					(whiskey_lexer.TokenID.MUL_ASSIGN, ASTID.EXPR_MUL_ASSIGN),
					(whiskey_lexer.TokenID.DIV_ASSIGN, ASTID.EXPR_DIV_ASSIGN),
					(whiskey_lexer.TokenID.DIV_INT_ASSIGN, ASTID.EXPR_DIV_INT_ASSIGN),
					(whiskey_lexer.TokenID.DIV_REAL_ASSIGN, ASTID.EXPR_DIV_REAL_ASSIGN),
					(whiskey_lexer.TokenID.EXP_ASSIGN, ASTID.EXPR_EXP_ASSIGN),
					(whiskey_lexer.TokenID.MOD_ASSIGN, ASTID.EXPR_MOD_ASSIGN),
					(whiskey_lexer.TokenID.BIT_SHL_ASSIGN, ASTID.EXPR_BIT_SHL_ASSIGN),
					(whiskey_lexer.TokenID.BIT_SHR_ASSIGN, ASTID.EXPR_BIT_SHR_ASSIGN),
					(whiskey_lexer.TokenID.BIT_AND_ASSIGN, ASTID.EXPR_BIT_AND_ASSIGN),
					(whiskey_lexer.TokenID.BIT_OR_ASSIGN, ASTID.EXPR_BIT_OR_ASSIGN),
					(whiskey_lexer.TokenID.BIT_XOR_ASSIGN, ASTID.EXPR_BIT_XOR_ASSIGN),
					(whiskey_lexer.TokenID.ASSIGN, ASTID.EXPR_ASSIGN)
				]
			)

	@staticmethod
	def rule_expr(parser):
		return parser.try_parse(WhiskeyParser.rule_expr_assign)

	@staticmethod
	def rule_type_symbol(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid == whiskey_lexer.TokenID.SYMBOL:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.SYMBOL,
					name = tok.text
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_BOOL:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_BOOL
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_INT:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_INT
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_INT8:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_INT8
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_INT16:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_INT16
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_INT32:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_INT32
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_INT64:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_INT64
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_BIGINT:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_BIGINT
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_UINT:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_UINT
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_UINT8:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_UINT8
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_UINT16:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_UINT16
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_UINT32:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_UINT32
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_UINT64:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_UINT64
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_BIGUINT:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_BIGUINT
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_CHAR:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_CHAR
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_CHAR8:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_CHAR8
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_CHAR16:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_CHAR16
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_CHAR32:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_CHAR32
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_RATIO:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_RATIO
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_RATIO8:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_RATIO8
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_RATIO16:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_RATIO16
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_RATIO32:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_RATIO32
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_RATIO64:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_RATIO64
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_BIGRATIO:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_BIGRATIO
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_FLOAT:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_FLOAT
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_FLOAT32:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_FLOAT32
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_FLOAT64:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_FLOAT64
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_REAL:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_REAL
				), True)
		elif tok.tid == whiskey_lexer.TokenID.KW_BIGREAL:
			parser.eat_token()
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TYPE_BIGREAL
				), True)
		else:
			return base_parser.ParserResult(None, False)

	@staticmethod
	def rule_type_group(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.LPAREN:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		rtn = parser.expect_parse(WhiskeyParser.rule_type)
		if not rtn.keep:
			return base_parser.ParserResult(None, False)

		parser.expect_token(whiskey_lexer.TokenID.RPAREN)

		return rtn

	@staticmethod
	def rule_type_term(parser):
		return parser.try_parse_anyof(
				WhiskeyParser.rule_type_symbol,
				WhiskeyParser.rule_type_group
			)

	@staticmethod
	def rule_type_templated(parser):
		templatee = parser.try_parse(WhiskeyParser.rule_type_term)
		if not templatee.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			return templatee

		tok = parser.get_token()
		if tok.tid == whiskey_lexer.TokenID.LT:
			parser.eat_token()

			args = []

			while parser.more_tokens():
				arg = parser.expect_parse(WhiskeyParser.rule_type)
				if not arg.keep:
					return base_parser.ParserResult(None, False)

				if not parser.more_tokens():
					raise base_parser.ParserError("unexpected end of stream")

				args.append(arg.ast)

				tok = parser.get_token()
				if tok.tid == whiskey_lexer.TokenID.COMMA:
					parser.eat_token()
					continue
				elif tok.tid == whiskey_lexer.TokenID.BIT_SHR_ASSIGN:
					parser.eat_token()
					parser.inject_token(token.Token("--", 0, 0, -1, whiskey_lexer.TokenID.GE, ">="))
					break
				elif tok.tid == whiskey_lexer.TokenID.BIT_SHR:
					parser.eat_token()
					parser.inject_token(token.Token("--", 0, 0, -1, whiskey_lexer.TokenID.GT, ">"))
					break
				elif tok.tid == whiskey_lexer.TokenID.GE:
					parser.eat_token()
					parser.inject_token(token.Token("--", 0, 0, -1, whiskey_lexer.TokenID.ASSIGN, "="))
					break
				elif tok.tid == whiskey_lexer.TokenID.GT:
					parser.eat_token()
					break
				elif tok.tid == whiskey_lexer.TokenID.BIT_SHR:
					parser.eat_token()
					continue

			return base_parser.ParserResult(ast.AST(
					templatee.ast.token,
					ASTID.TEMPLATE_EVAL,
					templatee = templatee.ast,
					args = args
				), True)
		else:
			return templatee

	@staticmethod
	def rule_type_access(parser):
		return parser.parse_binary(
				WhiskeyParser.rule_type_templated,
				WhiskeyParser.rule_type_access,
				[
					(whiskey_lexer.TokenID.PERIOD, ASTID.ACCESS)
				]
			)

	@staticmethod
	def rule_type_decorator(parser):
		return parser.parse_unary_right(
				WhiskeyParser.rule_type_decorator,
				WhiskeyParser.rule_type_access,
				[
					(whiskey_lexer.TokenID.COLON, ASTID.DECORATOR)
				]
			)

	@staticmethod
	def rule_type_decorated(parser):
		decorators = []

		while parser.more_tokens():
			if parser.get_token().tid == whiskey_lexer.TokenID.COLON:
				decorator = parser.try_parse(WhiskeyParser.rule_type_decorator)
				if not decorator.keep:
					return base_parser.ParserResult(None, False)

				decorators.append(decorator.ast)
			else:
				break

		if len(decorators) > 0:
			arg = parser.expect_parse(WhiskeyParser.rule_type_access)
			if not arg.keep:
				return base_parser.ParserResult(None, False)

			return base_parser.ParserResult(ast.AST(
					arg.ast.token,
					ASTID.DECORATED,
					decorators = decorators,
					arg = arg.ast
				), True)
		else:
			return parser.try_parse(WhiskeyParser.rule_type_access)

	@staticmethod
	def rule_type(parser):
		return parser.try_parse(WhiskeyParser.rule_type_decorated)

	@staticmethod
	def rule_stmt_noop(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.SEMICOLON:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		return base_parser.ParserResult(None, True)

	@staticmethod
	def rule_stmt_expr(parser):
		expr = parser.try_parse(WhiskeyParser.rule_expr)
		if not expr.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.SEMICOLON:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		return expr

	@staticmethod
	def rule_stmt_return(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_RETURN:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		args = parser.parse_bound_list(
				WhiskeyParser.rule_expr,
				whiskey_lexer.TokenID.COMMA,
				whiskey_lexer.TokenID.LPAREN,
				whiskey_lexer.TokenID.RPAREN
			)

		if not args.keep:
			return base_parser.ParserResult(None, False)

		if len(args.ast) > 1:
			raise base_parser.ParserError("return expects 0 or 1 argument")

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_RETURN,
				args = args.ast
			), True)

	@staticmethod
	def rule_stmt_throw(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_THROW:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		args = parser.parse_bound_list(
				WhiskeyParser.rule_expr,
				whiskey_lexer.TokenID.COMMA,
				whiskey_lexer.TokenID.LPAREN,
				whiskey_lexer.TokenID.RPAREN
			)

		if not args.keep:
			return base_parser.ParserResult(None, False)

		if len(args.ast) > 1:
			raise base_parser.ParserError("throw expects 0 or 1 argument")

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_THROW,
				args = args.ast
			), True)

	@staticmethod
	def rule_stmt_block(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.LBRACE:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		stmts = []

		while parser.more_tokens():
			if parser.get_token().tid == whiskey_lexer.TokenID.RBRACE:
				break

			stmt = parser.expect_parse(WhiskeyParser.rule_stmt)

			if not stmt.keep:
				return base_parser.ParserResult(None, False)

			stmts.append(stmt.ast)

		parser.expect_token(whiskey_lexer.TokenID.RBRACE)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_BLOCK,
				stmts = stmts
			), True)

	@staticmethod
	def rule_stmt_if(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_IF:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		args = parser.parse_bound_list(
				WhiskeyParser.rule_expr,
				whiskey_lexer.TokenID.COMMA,
				whiskey_lexer.TokenID.LPAREN,
				whiskey_lexer.TokenID.RPAREN
			)

		if not args.keep:
			return base_parser.ParserResult(None, False)

		if len(args.ast) != 1:
			raise base_parser.ParserError("if expects 1 argument")

		then = parser.expect_parse(WhiskeyParser.rule_stmt)
		if not then.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.STMT_IF,
					condition = args.ast[0],
					then = then.ast
				), True)
		elif parser.get_token().tid != whiskey_lexer.TokenID.KW_ELSE:
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.STMT_IF,
					condition = args.ast[0],
					then = then.ast
				), True)
		else:
			parser.eat_token()
			_else = parser.expect_parse(WhiskeyParser.rule_stmt)
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.STMT_IF,
					condition = args.ast[0],
					then = then.ast,
					_else = _else.ast
				), True)

	@staticmethod
	def rule_stmt_while(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_WHILE:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		args = parser.parse_bound_list(
				WhiskeyParser.rule_expr,
				whiskey_lexer.TokenID.COMMA,
				whiskey_lexer.TokenID.LPAREN,
				whiskey_lexer.TokenID.RPAREN
			)

		if not args.keep:
			return base_parser.ParserResult(None, False)

		if len(args.ast) != 1:
			raise base_parser.ParserError("while expects 1 argument")

		body = parser.expect_parse(WhiskeyParser.rule_stmt)
		if not body.keep:
			return base_parser.ParserResult(None, False)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_WHILE,
				condition = args.ast[0],
				body = body.ast
			), True)

	@staticmethod
	def rule_stmt_for(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_FOR:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.LPAREN)

		inits = []
		while parser.more_tokens():
			tok2 = parser.get_token()
			if tok2.tid == whiskey_lexer.TokenID.SEMICOLON:
				break

			init = parser.expect_parse(WhiskeyParser.rule_decl_var_no_semicolon)
			if not init.keep:
				return base_parser.ParserResult(None, False)

			inits.append(init.ast)

			if not parser.more_tokens():
				raise base_parser.ParserError("unexpected end of stream")

			tok2 = parser.get_token()
			if tok2.tid == whiskey_lexer.TokenID.COMMA:
				parser.eat_token()
				continue
			elif tok2.tid == whiskey_lexer.TokenID.SEMICOLON:
				break

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		condition = None

		if parser.get_token().tid != whiskey_lexer.TokenID.SEMICOLON:
			condition = parser.expect_parse(WhiskeyParser.rule_expr)
			if not condition.keep:
				return base_parser.ParserResult(None, False)

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		steps = []
		while parser.more_tokens():
			tok2 = parser.get_token()
			if tok2.tid == whiskey_lexer.TokenID.RPAREN:
				break

			step = parser.expect_parse(WhiskeyParser.rule_expr)
			if not step.keep:
				return base_parser.ParserResult(None, False)

			steps.append(step.ast)

			if not parser.more_tokens():
				raise base_parser.ParserError("unexpected end of stream")

			tok2 = parser.get_token()
			if tok2.tid == whiskey_lexer.TokenID.COMMA:
				parser.eat_token()
				continue
			elif tok2.tid == whiskey_lexer.TokenID.RPAREN:
				break

		parser.expect_token(whiskey_lexer.TokenID.RPAREN)

		body = parser.expect_parse(WhiskeyParser.rule_stmt)
		if not body.keep:
			return base_parser.ParserResult(None, False)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_FOR,
				inits = inits,
				condition = condition.ast,
				steps = steps,
				body = body.ast
			), True)

	@staticmethod
	def rule_stmt_foreach(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_FOREACH:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.LPAREN)

		value = parser.expect_parse(WhiskeyParser.rule_decl_var)

		sequence = parser.expect_parse(WhiskeyParser.rule_expr)

		parser.expect_token(whiskey_lexer.TokenID.RPAREN)

		body = parser.expect_parse(WhiskeyParser.rule_stmt)
		if not body.keep:
			return base_parser.ParserResult(None, False)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_FOREACH,
				value = value.ast,
				sequence = sequence.ast,
				body = body.ast
			), True)

	@staticmethod
	def rule_stmt_catch(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_CATCH:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.LPAREN)

		exception = parser.try_parse(WhiskeyParser.rule_decl_var_no_semicolon)
		if not exception.keep:
			exception = parser.expect_parse(WhiskeyParser.rule_type)

		parser.expect_token(whiskey_lexer.TokenID.RPAREN)

		body = parser.expect_parse(WhiskeyParser.rule_stmt)
		if not body.keep:
			return base_parser.ParserResult(None, False)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_CATCH,
				exception = exception.ast,
				body = body.ast
			), True)

	@staticmethod
	def rule_stmt_try(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)
		
		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.KW_TRY:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		body = parser.expect_parse(WhiskeyParser.rule_stmt)
		if not body.keep:
			return base_parser.ParserResult(None, False)

		catches = []

		while parser.more_tokens():
			tok2 = parser.get_token()
			if not tok2.tid == whiskey_lexer.TokenID.KW_CATCH:
				break

			catch = parser.expect_parse(WhiskeyParser.rule_stmt_catch)
			if not catch.keep:
				return base_parser.ParserResult(None, False)

			catches.append(catch.ast)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.STMT_TRY,
				body = body.ast,
				catches = catches
			), True)

	@staticmethod
	def rule_stmt(parser):
		return parser.try_parse_anyof(
				WhiskeyParser.rule_stmt_noop,
				WhiskeyParser.rule_stmt_block,
				WhiskeyParser.rule_stmt_return,
				WhiskeyParser.rule_stmt_throw,
				WhiskeyParser.rule_stmt_if,
				WhiskeyParser.rule_stmt_while,
				WhiskeyParser.rule_stmt_for,
				WhiskeyParser.rule_stmt_foreach,
				WhiskeyParser.rule_stmt_try,
				WhiskeyParser.rule_stmt_expr
			)

	@staticmethod
	def rule_template_decl_arg_type(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		if parser.get_token().tid == whiskey_lexer.TokenID.SYMBOL:
			if parser.get_token().text == "type":
				tok = parser.eat_token()
				arg = parser.expect_parse(WhiskeyParser.rule_type)
				if not arg.keep:
					return base_parser.ParserResult(None, False)
				return base_parser.ParserResult(ast.AST(
						tok,
						ASTID.TEMPLATE_DECL_ARG_TYPE,
						arg = arg.ast
					), True)
			else:
				return base_parser.ParserResult(None, False)
		else:
			return base_parser.ParserResult(None, False)

	@staticmethod
	def rule_template_decl_arg(parser):
		return parser.try_parse_anyof(
				WhiskeyParser.rule_template_decl_arg_type,
				WhiskeyParser.rule_decl_var_no_semicolon
			)

	@staticmethod
	def rule_template_decl(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.SYMBOL:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		if not parser.more_tokens():
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.SYMBOL,
					name = tok.text
				), True)

		if parser.get_token().tid == whiskey_lexer.TokenID.LT:
			args = parser.parse_bound_list(
					WhiskeyParser.rule_template_decl_arg,
					whiskey_lexer.TokenID.COMMA,
					whiskey_lexer.TokenID.LT,
					whiskey_lexer.TokenID.GT
				)

			if not args.keep:
				return base_parser.ParserResult(None, False)

			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.TEMPLATE_DECL,
					name = tok.text,
					args = args.ast
				), True)
		else:
			return base_parser.ParserResult(ast.AST(
					tok,
					ASTID.SYMBOL,
					name = tok.text
				), True)

	@staticmethod
	def rule_decl_var_no_semicolon(parser):
		decl_type = parser.try_parse(WhiskeyParser.rule_type)
		if not decl_type.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		symbol = parser.try_parse(WhiskeyParser.rule_template_decl)
		if not symbol.keep:
			return base_parser.ParserResult(None, False)

		if parser.more_tokens():
			tok = parser.get_token()
			if tok.tid == whiskey_lexer.TokenID.ASSIGN:
				parser.eat_token()

				decl_value = parser.expect_parse(WhiskeyParser.rule_expr)

				return base_parser.ParserResult(ast.AST(
						symbol.ast.token,
						ASTID.DECL_VAR,
						symbol = symbol.ast,
						type = decl_type.ast,
						value = decl_value.ast
					), True)
			else:
				return base_parser.ParserResult(ast.AST(
						symbol.ast.token,
						ASTID.DECL_VAR,
						symbol = symbol.ast,
						type = decl_type.ast
					), True)
		else:
			return base_parser.ParserResult(ast.AST(
					symbol.ast.token,
					ASTID.DECL_VAR,
					symbol = symbol.ast,
					type = decl_type.ast
				), True)

	@staticmethod
	def rule_decl_var(parser):
		rtn = parser.try_parse(WhiskeyParser.rule_decl_var_no_semicolon)
		if not rtn.keep:
			return base_parser.ParserResult(None, False)

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		return rtn

	@staticmethod
	def rule_decl_func(parser):
		ret_type = parser.try_parse(WhiskeyParser.rule_type)
		if not ret_type.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.SYMBOL:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		lparen = parser.get_token()
		if lparen.tid != whiskey_lexer.TokenID.LPAREN:
			return base_parser.ParserResult(None, False)

		args = parser.parse_bound_list(
				WhiskeyParser.rule_decl_var_no_semicolon,
				whiskey_lexer.TokenID.COMMA,
				whiskey_lexer.TokenID.LPAREN,
				whiskey_lexer.TokenID.RPAREN
			)

		if not args.keep:
			return base_parser.ParserResult(None, False)
	
		if not parser.more_tokens():
			raise base_parser.ParserError("unexpected end of stream")

		tok2 = parser.get_token()
		body = None
		if tok2.tid == whiskey_lexer.TokenID.SEMICOLON:
			parser.eat_token()
		elif tok2.tid == whiskey_lexer.TokenID.ASSIGN:
			parser.eat_token()
			body = parser.expect_parse(WhiskeyParser.rule_stmt_expr)
			if not body.keep:
				return base_parser.ParserResult(None, False)
			else:
				body = body.ast
		else:
			body = parser.expect_parse(WhiskeyParser.rule_stmt_block)
			if not body.keep:
				return base_parser.ParserResult(None, False)
			else:
				body = body.ast

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.DECL_FUNC,
				ret_type = ret_type.ast,
				args = args.ast,
				body = body
			), True)

	@staticmethod
	def rule_decl_block(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if tok.tid != whiskey_lexer.TokenID.LBRACE:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		decls = []

		while parser.more_tokens():
			if parser.get_token().tid == whiskey_lexer.TokenID.RBRACE:
				break

			decl = parser.expect_parse(WhiskeyParser.rule_decl)

			if not decl.keep:
				return base_parser.ParserResult(None, False)

			if type(decl) == list:
				decls += decl
			else:
				decls.append(decl.ast)

		parser.expect_token(whiskey_lexer.TokenID.RBRACE)

		return base_parser.ParserResult(decls, True)

	@staticmethod
	def rule_decl_class_undecorated(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if not tok.tid == whiskey_lexer.TokenID.KW_CLASS:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		symbol = parser.expect_parse(WhiskeyParser.rule_template_decl)
		if not symbol.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			raise base_parser.ParserError("unexpected end of stream")

		tok2 = parser.get_token()
		inherits = []
		if tok2.tid == whiskey_lexer.TokenID.KW_INHERITS:
			parser.eat_token()

			while parser.more_tokens():
				tmp = parser.expect_parse(WhiskeyParser.rule_type)
				if not tmp.keep:
					return base_parser.ParserResult(None, False)

				inherits.append(tmp.ast)

				if parser.more_tokens() and parser.get_token().tid == whiskey_lexer.TokenID.LBRACE:
					break
				elif parser.more_tokens() and parser.get_token().tid == whiskey_lexer.TokenID.COMMA:
					parser.eat_token()

		body = parser.expect_parse(WhiskeyParser.rule_decl_block)
		if not body.keep:
			return base_parser.ParserResult(None, False)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.DECL_CLASS,
				decorators = [],
				symbol = symbol.ast,
				inherits = inherits,
				body = body.ast
			), True)

	@staticmethod
	def rule_decl_class(parser):
		decorators = []

		while parser.more_tokens():
			if parser.get_token().tid == whiskey_lexer.TokenID.COLON:
				decorator = parser.try_parse(WhiskeyParser.rule_type_decorator)
				if not decorator.keep:
					return base_parser.ParserResult(None, False)

				decorators.append(decorator.ast)
			else:
				break

		arg = parser.try_parse(WhiskeyParser.rule_decl_class_undecorated)
		if not arg.keep:
			return base_parser.ParserResult(None, False)

		arg.ast.fields["decorators"] = decorators
		return arg

	@staticmethod
	def rule_decl_enum_undecorated(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if not tok.tid == whiskey_lexer.TokenID.KW_ENUM:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		symbol = parser.expect_parse(WhiskeyParser.rule_type_symbol)
		if not symbol.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			raise base_parser.ParserError("unexpected end of stream")

		tok2 = parser.get_token()
		inherits = []
		if tok2.tid == whiskey_lexer.TokenID.KW_INHERITS:
			parser.eat_token()

			while parser.more_tokens():
				tmp = parser.expect_parse(WhiskeyParser.rule_type)
				if not tmp.keep:
					return base_parser.ParserResult(None, False)

				inherits.append(tmp.ast)

				if parser.more_tokens() and parser.get_token().tid == whiskey_lexer.TokenID.LBRACE:
					break
				elif parser.more_tokens() and parser.get_token().tid == whiskey_lexer.TokenID.COMMA:
					parser.eat_token()

		if not parser.more_tokens():
			raise base_parser.ParserError("unexpected end of stream")

		parser.expect_token(whiskey_lexer.TokenID.LBRACE)

		values = []

		while parser.more_tokens():
			if parser.get_token().tid == whiskey_lexer.TokenID.RBRACE:
				break
			elif parser.get_token().tid == whiskey_lexer.TokenID.SEMICOLON:
				parser.eat_token()
				break
			elif parser.get_token().tid == whiskey_lexer.TokenID.SYMBOL:
				values.append(parser.get_token().text)
				parser.eat_token()

				if not parser.more_tokens():
					raise base_parser.ParserError("unexpected end of stream")
				elif parser.get_token().tid == whiskey_lexer.TokenID.COMMA:
					parser.eat_token()
			else:
				raise base_parser.ParserError("unexpected token " + repr(parser.get_token()) + ", expected enumeration value")
		
		decls = []

		while parser.more_tokens():
			if parser.get_token().tid == whiskey_lexer.TokenID.RBRACE:
				break

			decl = parser.expect_parse(WhiskeyParser.rule_decl)

			if not decl.keep:
				return base_parser.ParserResult(None, False)

			if type(decl) == list:
				decls += decl
			else:
				decls.append(decl.ast)

		parser.expect_token(whiskey_lexer.TokenID.RBRACE)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.DECL_ENUM,
				decorators = [],
				symbol = symbol.ast,
				inherits = inherits,
				values = values,
				decls = decls
			), True)

	@staticmethod
	def rule_decl_enum(parser):
		decorators = []

		while parser.more_tokens():
			if parser.get_token().tid == whiskey_lexer.TokenID.COLON:
				decorator = parser.try_parse(WhiskeyParser.rule_type_decorator)
				if not decorator.keep:
					return base_parser.ParserResult(None, False)

				decorators.append(decorator.ast)
			else:
				break

		arg = parser.try_parse(WhiskeyParser.rule_decl_enum_undecorated)
		if not arg.keep:
			return base_parser.ParserResult(None, False)

		arg.ast.fields["decorators"] = decorators
		return arg

	@staticmethod
	def rule_decl_namespace(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if not tok.tid == whiskey_lexer.TokenID.KW_NAMESPACE:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		symbol = parser.expect_parse(WhiskeyParser.rule_type_access)
		if not symbol.keep:
			return base_parser.ParserResult(None, False)

		if not parser.more_tokens():
			raise base_parser.ParserError("unexpected end of stream")

		body = parser.expect_parse(WhiskeyParser.rule_decl_block)
		if not body.keep:
			return base_parser.ParserResult(None, False)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.DECL_NAMESPACE,
				symbol = symbol.ast,
				body = body.ast
			), True)

	@staticmethod
	def rule_decl(parser):
		return parser.try_parse_anyof(
				WhiskeyParser.rule_decl_class,
				WhiskeyParser.rule_decl_namespace,
				WhiskeyParser.rule_decl_enum,
				WhiskeyParser.rule_decl_func,
				WhiskeyParser.rule_decl_var
			)

	@staticmethod
	def rule_toplevel_import(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if not tok.tid == whiskey_lexer.TokenID.KW_IMPORT:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.LPAREN)

		if not parser.more_tokens():
			raise base_parser.ParserError("unexpected end of stream")

		tok2 = parser.get_token()
		if tok2.tid != whiskey_lexer.TokenID.LITERAL_STRING:
			raise base_parser.ParserError("expected literal string, not " + repr(tok2))

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.RPAREN)

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.TOPLEVEL_IMPORT,
				path = bytes(tok2.text[1:-1], "utf-8").decode("unicode_escape")
			), True)

	@staticmethod
	def rule_toplevel_import_using(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if not tok.tid == whiskey_lexer.TokenID.KW_IMPORT_USING:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.LPAREN)

		if not parser.more_tokens():
			raise base_parser.ParserError("unexpected end of stream")

		tok2 = parser.get_token()
		if tok2.tid != whiskey_lexer.TokenID.LITERAL_STRING:
			raise base_parser.ParserError("expected literal string, not " + repr(tok2))

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.RPAREN)

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.TOPLEVEL_IMPORT_USING,
				path = bytes(tok2.text[1:-1], "utf-8").decode("unicode_escape")
			), True)

	@staticmethod
	def rule_toplevel_using(parser):
		if not parser.more_tokens():
			return base_parser.ParserResult(None, False)

		tok = parser.get_token()
		if not tok.tid == whiskey_lexer.TokenID.KW_USING:
			return base_parser.ParserResult(None, False)

		parser.eat_token()

		parser.expect_token(whiskey_lexer.TokenID.LPAREN)

		path = parser.expect_parse(WhiskeyParser.rule_type_access)
		if not path.keep:
			return base_parser.ParserResult(None, False)

		parser.expect_token(whiskey_lexer.TokenID.RPAREN)

		parser.expect_token(whiskey_lexer.TokenID.SEMICOLON)

		return base_parser.ParserResult(ast.AST(
				tok,
				ASTID.TOPLEVEL_USING,
				path = path.ast
			), True)

	@staticmethod
	def rule_toplevel(parser):
		return parser.try_parse_anyof(
				WhiskeyParser.rule_toplevel_import,
				WhiskeyParser.rule_toplevel_import_using,
				WhiskeyParser.rule_toplevel_using,
				WhiskeyParser.rule_decl
			)

	@staticmethod
	def rule_page(parser):
		rtn = []

		while parser.more_tokens():
			tmp = parser.try_parse(WhiskeyParser.rule_toplevel)
			if not tmp.keep:
				return base_parser.ParserResult(None, False)

			rtn.append(tmp.ast)

		return base_parser.ParserResult(ast.AST(
				token.Token("--", 0, 0, -1, None, "") if len(rtn) == 0 else rtn[0].token,
				ASTID.PAGE,
				children = rtn
			), True)

	def parse(self):
		res = self.try_parse(WhiskeyParser.rule_page)
		if self.more_tokens():
			raise base_parser.ParserError("not all tokens parsed, stopped at " + repr(self.get_token()))
		return res
