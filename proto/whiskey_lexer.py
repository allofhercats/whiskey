import enum
import string

import base_lexer

@enum.unique
class TokenID(enum.Enum):
	SYMBOL = enum.auto()
	KW_TRUE = enum.auto()
	KW_FALSE = enum.auto()
	KW_NOT = enum.auto()
	KW_AND = enum.auto()
	KW_OR = enum.auto()
	KW_BOOL = enum.auto()
	KW_INT = enum.auto()
	KW_INT8 = enum.auto()
	KW_INT16 = enum.auto()
	KW_INT32 = enum.auto()
	KW_INT64 = enum.auto()
	KW_BIGINT = enum.auto()
	KW_UINT = enum.auto()
	KW_UINT8 = enum.auto()
	KW_UINT16 = enum.auto()
	KW_UINT32 = enum.auto()
	KW_UINT64 = enum.auto()
	KW_BIGUINT = enum.auto()
	KW_CHAR = enum.auto()
	KW_CHAR8 = enum.auto()
	KW_CHAR16 = enum.auto()
	KW_CHAR32 = enum.auto()
	KW_RATIO = enum.auto()
	KW_RATIO8 = enum.auto()
	KW_RATIO16 = enum.auto()
	KW_RATIO32 = enum.auto()
	KW_RATIO64 = enum.auto()
	KW_BIGRATIO = enum.auto()
	KW_FLOAT = enum.auto()
	KW_FLOAT32 = enum.auto()
	KW_FLOAT64 = enum.auto()
	KW_REAL = enum.auto()
	KW_BIGREAL = enum.auto()
	KW_RETURN = enum.auto()
	KW_THROW = enum.auto()
	KW_TRY = enum.auto()
	KW_CATCH = enum.auto()
	KW_IF = enum.auto()
	KW_ELSE = enum.auto()
	KW_WHILE = enum.auto()
	KW_FOR = enum.auto()
	KW_FOREACH = enum.auto()
	KW_CONTINUE = enum.auto()
	KW_BREAK = enum.auto()
	KW_CLASS = enum.auto()
	KW_NEW = enum.auto()
	KW_DELETE = enum.auto()
	KW_INHERITS = enum.auto()
	KW_ENUM = enum.auto()
	KW_NAMESPACE = enum.auto()
	KW_IMPORT = enum.auto()
	KW_IMPORT_USING = enum.auto()
	KW_USING = enum.auto()
	LITERAL_INT = enum.auto()
	LITERAL_FLOAT = enum.auto()
	LITERAL_CHAR = enum.auto()
	LITERAL_STRING = enum.auto()
	LPAREN = enum.auto()
	RPAREN = enum.auto()
	COMMA = enum.auto()
	LBRACE = enum.auto()
	RBRACE = enum.auto()
	SEMICOLON = enum.auto()
	COLON = enum.auto()
	PERIOD = enum.auto()
	ADD = enum.auto()
	INC = enum.auto()
	ADD_ASSIGN = enum.auto()
	SUB = enum.auto()
	DEC = enum.auto()
	SUB_ASSIGN = enum.auto()
	MUL = enum.auto()
	EXP = enum.auto()
	EXP_ASSIGN = enum.auto()
	MUL_ASSIGN = enum.auto()
	DIV = enum.auto()
	DIV_INT = enum.auto()
	DIV_INT_ASSIGN = enum.auto()
	DIV_REAL = enum.auto()
	DIV_REAL_ASSIGN = enum.auto()
	DIV_ASSIGN = enum.auto()
	MOD = enum.auto()
	MOD_ASSIGN = enum.auto()
	BIT_AND = enum.auto()
	BIT_AND_ASSIGN = enum.auto()
	BIT_OR = enum.auto()
	BIT_OR_ASSIGN = enum.auto()
	BIT_XOR = enum.auto()
	BIT_XOR_ASSIGN = enum.auto()
	BIT_SHL = enum.auto()
	BIT_SHL_ASSIGN = enum.auto()
	BIT_SHR = enum.auto()
	BIT_SHR_ASSIGN = enum.auto()
	BIT_NOT = enum.auto()
	LT = enum.auto()
	LE = enum.auto()
	GT = enum.auto()
	GE = enum.auto()
	NE = enum.auto()
	EQ = enum.auto()
	ASSIGN = enum.auto()
	BOOL_IMPLIES = enum.auto()

class WhiskeyLexer(base_lexer.BaseLexer):
	def lex(self):
		while self.more_chrs():
			if self.get_chr() in " \t\r\n":
				self.eat_chr()
				self.skip_token()
			elif self.get_chr() == "#":
				self.eat_chr()
				if self.get_chr() == "{":
					last = None
					while self.more_chrs():
						if last == "}" and self.get_chr() == "#":
							break
						else:
							last = self.eat_chr()
					if not self.eat_chr() == "#":
						raise base_lexer.LexingError("#{ expects closing }#")
					self.skip_token()
				else:
					while self.more_chrs():
						if self.get_chr() in "\r\n":
							break
						else:
							self.eat_chr()
					self.skip_token()
			elif self.get_chr() in string.ascii_letters + "_":
				self.eat_chr()
				while self.more_chrs():
					if self.get_chr() in string.ascii_letters + string.digits + "_":
						self.eat_chr()
					else:
						break
				while self.more_chrs() and self.get_chr() == '\'':
					self.eat_chr()
				if self.get_text() == "true":
					self.emit_token(TokenID.KW_TRUE)
				elif self.get_text() == "false":
					self.emit_token(TokenID.KW_FALSE)
				elif self.get_text() == "not":
					self.emit_token(TokenID.KW_NOT)
				elif self.get_text() == "and":
					self.emit_token(TokenID.KW_AND)
				elif self.get_text() == "or":
					self.emit_token(TokenID.KW_OR)
				elif self.get_text() == "bool":
					self.emit_token(TokenID.KW_BOOL)
				elif self.get_text() == "int":
					self.emit_token(TokenID.KW_INT)
				elif self.get_text() == "int8":
					self.emit_token(TokenID.KW_INT8)
				elif self.get_text() == "int16":
					self.emit_token(TokenID.KW_INT16)
				elif self.get_text() == "int32":
					self.emit_token(TokenID.KW_INT32)
				elif self.get_text() == "int64":
					self.emit_token(TokenID.KW_INT64)
				elif self.get_text() == "bigint":
					self.emit_token(TokenID.KW_BIGINT)
				elif self.get_text() == "uint":
					self.emit_token(TokenID.KW_UINT)
				elif self.get_text() == "uint8":
					self.emit_token(TokenID.KW_UINT8)
				elif self.get_text() == "uint16":
					self.emit_token(TokenID.KW_UINT16)
				elif self.get_text() == "uint32":
					self.emit_token(TokenID.KW_UINT32)
				elif self.get_text() == "uint64":
					self.emit_token(TokenID.KW_UINT64)
				elif self.get_text() == "biguint":
					self.emit_token(TokenID.KW_BIGUINT)
				elif self.get_text() == "char":
					self.emit_token(TokenID.KW_CHAR)
				elif self.get_text() == "char8":
					self.emit_token(TokenID.KW_CHAR8)
				elif self.get_text() == "char16":
					self.emit_token(TokenID.KW_CHAR16)
				elif self.get_text() == "char32":
					self.emit_token(TokenID.KW_CHAR32)
				elif self.get_text() == "ratio":
					self.emit_token(TokenID.KW_RATIO)
				elif self.get_text() == "ratio8":
					self.emit_token(TokenID.KW_RATIO8)
				elif self.get_text() == "ratio16":
					self.emit_token(TokenID.KW_RATIO16)
				elif self.get_text() == "ratio32":
					self.emit_token(TokenID.KW_RATIO32)
				elif self.get_text() == "ratio64":
					self.emit_token(TokenID.KW_RATIO64)
				elif self.get_text() == "bigratio":
					self.emit_token(TokenID.KW_BIGRATIO)
				elif self.get_text() == "float":
					self.emit_token(TokenID.KW_FLOAT)
				elif self.get_text() == "float32":
					self.emit_token(TokenID.KW_FLOAT32)
				elif self.get_text() == "float64":
					self.emit_token(TokenID.KW_FLOAT64)
				elif self.get_text() == "real":
					self.emit_token(TokenID.KW_REAL)
				elif self.get_text() == "bigreal":
					self.emit_token(TokenID.KW_BIGREAL)
				elif self.get_text() == "return":
					self.emit_token(TokenID.KW_RETURN)
				elif self.get_text() == "throw":
					self.emit_token(TokenID.KW_THROW)
				elif self.get_text() == "try":
					self.emit_token(TokenID.KW_TRY)
				elif self.get_text() == "catch":
					self.emit_token(TokenID.KW_CATCH)
				elif self.get_text() == "if":
					self.emit_token(TokenID.KW_IF)
				elif self.get_text() == "else":
					self.emit_token(TokenID.KW_ELSE)
				elif self.get_text() == "while":
					self.emit_token(TokenID.KW_WHILE)
				elif self.get_text() == "for":
					self.emit_token(TokenID.KW_FOR)
				elif self.get_text() == "foreach":
					self.emit_token(TokenID.KW_FOREACH)
				elif self.get_text() == "continue":
					self.emit_token(TokenID.KW_CONTINUE)
				elif self.get_text() == "break":
					self.emit_token(TokenID.KW_BREAK)
				elif self.get_text() == "class":
					self.emit_token(TokenID.KW_CLASS)
				elif self.get_text() == "new":
					self.emit_token(TokenID.KW_NEW)
				elif self.get_text() == "delete":
					self.emit_token(TokenID.KW_DELETE)
				elif self.get_text() == "inherits":
					self.emit_token(TokenID.KW_INHERITS)
				elif self.get_text() == "enum":
					self.emit_token(TokenID.KW_ENUM)
				elif self.get_text() == "namespace":
					self.emit_token(TokenID.KW_NAMESPACE)
				elif self.get_text() == "import":
					self.emit_token(TokenID.KW_IMPORT)
				elif self.get_text() == "import_using":
					self.emit_token(TokenID.KW_IMPORT_USING)
				elif self.get_text() == "using":
					self.emit_token(TokenID.KW_USING)
				else:
					self.emit_token(TokenID.SYMBOL)
			elif self.get_chr() in string.digits:
				self.eat_chr()
				while self.more_chrs() and self.get_chr() in string.digits + string.ascii_letters:
					self.eat_chr()

				if self.get_chr() == '.':
					if self.get_chr(1) in string.digits:
						self.eat_chr()
						while self.more_chrs() and self.get_chr() in string.digits + string.ascii_letters:
							self.eat_chr()
						self.emit_token(TokenID.LITERAL_FLOAT)
					else:
						self.emit_token(TokenID.LITERAL_INT)
				else:
					self.emit_token(TokenID.LITERAL_INT)
			elif self.get_chr() == '\'':
				self.eat_chr()
				last = None
				while self.more_chrs():
					if last != '\\' and self.get_chr() == '\'':
						break
					else:
						last = self.eat_chr()
				if not self.eat_chr() == '\'':
					raise base_lexer.LexingError("\' expects closing \'")
				self.emit_token(TokenID.LITERAL_CHAR)
			elif self.get_chr() == '\"':
				self.eat_chr()
				last = None
				while self.more_chrs():
					if last != '\\' and self.get_chr() == '\"':
						break
					else:
						last = self.eat_chr()
				if not self.eat_chr() == '\"':
					raise base_lexer.LexingError("\" expects closing \"")
				self.emit_token(TokenID.LITERAL_STRING)
			elif self.get_chr() == '(':
				self.eat_chr()
				self.emit_token(TokenID.LPAREN)
			elif self.get_chr() == ')':
				self.eat_chr()
				self.emit_token(TokenID.RPAREN)
			elif self.get_chr() == ',':
				self.eat_chr()
				self.emit_token(TokenID.COMMA)
			elif self.get_chr() == '{':
				self.eat_chr()
				self.emit_token(TokenID.LBRACE)
			elif self.get_chr() == '}':
				self.eat_chr()
				self.emit_token(TokenID.RBRACE)
			elif self.get_chr() == ';':
				self.eat_chr()
				self.emit_token(TokenID.SEMICOLON)
			elif self.get_chr() == ':':
				self.eat_chr()
				self.emit_token(TokenID.COLON)
			elif self.get_chr() == '.':
				self.eat_chr()
				self.emit_token(TokenID.PERIOD)
			elif self.get_chr() == '+':
				self.eat_chr()
				if self.get_chr() == '+':
					self.eat_chr()
					self.emit_token(TokenID.INC)
				elif self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.ADD_ASSIGN)
				else:
					self.emit_token(TokenID.ADD)
			elif self.get_chr() == '-':
				self.eat_chr()
				if self.get_chr() == '-':
					self.eat_chr()
					self.emit_token(TokenID.DEC)
				elif self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.SUB_ASSIGN)
				else:
					self.emit_token(TokenID.SUB)
			elif self.get_chr() == '*':
				self.eat_chr()
				if self.get_chr() == '*':
					self.eat_chr()
					if self.get_chr() == '=':
						self.eat_chr()
						self.emit_token(TokenID.EXP_ASSIGN)
					else:
						self.emit_token(TokenID.EXP)
				elif self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.MUL_ASSIGN)
				else:
					self.emit_token(TokenID.MUL)
			elif self.get_chr() == '/':
				self.eat_chr()
				if self.get_chr() == '/':
					self.eat_chr()
					if self.get_chr() == '=':
						self.eat_chr()
						self.emit_token(TokenID.DIV_INT_ASSIGN)
					else:
						self.emit_token(TokenID.DIV_INT)
				elif self.get_chr() == '.':
					self.eat_chr()
					if self.get_chr() == '=':
						self.eat_chr()
						self.emit_token(TokenID.DIV_REAL_ASSIGN)
					else:
						self.emit_token(TokenID.DIV_REAL)
				elif self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.DIV_ASSIGN)
				else:
					self.emit_token(TokenID.DIV)
			elif self.get_chr() == '%':
				self.eat_chr()
				if self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.MOD_ASSIGN)
				else:
					self.emit_token(TokenID.MOD)
			elif self.get_chr() == '&':
				self.eat_chr()
				if self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.BIT_AND_ASSIGN)
				else:
					self.emit_token(TokenID.BIT_AND)
			elif self.get_chr() == '|':
				self.eat_chr()
				if self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.BIT_OR_ASSIGN)
				else:
					self.emit_token(TokenID.BIT_OR)
			elif self.get_chr() == '^':
				self.eat_chr()
				if self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.BIT_OR_ASSIGN)
				else:
					self.emit_token(TokenID.BIT_OR)
			elif self.get_chr() == '~':
				self.eat_chr()
				self.emit_token(TokenID.BIT_NOT)
			elif self.get_chr() == '<':
				self.eat_chr()
				if self.get_chr() == '<':
					self.eat_chr()
					if self.get_chr() == '=':
						self.eat_chr()
						self.emit_token(TokenID.BIT_SHL_ASSIGN)
					else:
						self.emit_token(TokenID.BIT_SHL)
				elif self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.LE)
				else:
					self.emit_token(TokenID.LT)
			elif self.get_chr() == '>':
				self.eat_chr()
				if self.get_chr() == '>':
					self.eat_chr()
					if self.get_chr() == '=':
						self.eat_chr()
						self.emit_token(TokenID.BIT_SHR_ASSIGN)
					else:
						self.emit_token(TokenID.BIT_SHR)
				elif self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.GE)
				else:
					self.emit_token(TokenID.GT)
			elif self.get_chr() == '!':
				self.eat_chr()
				if self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.NE)
				else:
					raise base_lexer.LexingError("! can only be part of != operator")
			elif self.get_chr() == '=':
				self.eat_chr()
				if self.get_chr() == '=':
					self.eat_chr()
					self.emit_token(TokenID.EQ)
				elif self.get_chr() == '>':
					self.eat_chr()
					self.emit_token(TokenID.BOOL_IMPLIES)
				else:
					self.emit_token(TokenID.ASSIGN)
			else:
				raise base_lexer.LexingError("unexpected character " + repr(self.get_chr()))
