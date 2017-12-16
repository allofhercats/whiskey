import token
import ast

class ParserError(Exception):
	pass

class ParserResult(object):
	def __init__(self, ast, keep):
		self.ast = ast
		self.keep = keep

class BaseParser(object):
	def __init__(self, lexer):
		self.lexer = lexer
		self.offset = 0
		self.injected = []

	def get_token(self):
		if len(self.injected) > 0:
			return self.injected[0]
		elif self.more_tokens():
			return self.lexer.tokens[self.offset]
		else:
			return None

	def eat_token(self):
		if len(self.injected) > 0:
			tok = self.injected[0]
			del self.injected[0]
			return tok
		else:
			rtn = self.get_token()
			if rtn is not None:
				self.offset += 1
			return rtn

	def inject_token(self, token):
		self.injected.insert(0, token)

	def more_tokens(self):
		return self.offset < len(self.lexer.tokens) or len(self.injected) > 0

	def try_token(self, tid):
		if self.more_tokens() and self.get_token().tid == tid:
			return self.eat_token()
		else:
			return None

	def expect_token(self, tid):
		res = self.try_token(tid)
		if not res:
			raise ParserError("unexpected token " + repr(self.get_token()))

	def try_parse(self, rule):
		save_offset = self.offset
		res = rule(self)
		if not res.keep:
			self.offset = save_offset
		return res

	def expect_parse(self, rule):
		res = self.try_parse(rule)
		if not res.keep:
			raise ParserError("unexpected token " + repr(self.get_token()))
		return res

	def try_parse_anyof(self, *rules):
		for i in rules:
			res = self.try_parse(i)
			if res.keep:
				return res
		return ParserResult(None, False)

	def expect_parse_anyof(self, *rules):
		res = self.try_parse_anyof(rules)
		if not res.keep:
			raise ParserError("unexpected token " + repr(self.get_token()))
		return res

	def parse_bound(self, rule, left, right):
		if not self.more_tokens():
			raise ParserError("unexpected end of stream")

		if self.get_token().tid == left:
			self.eat_token()

			arg = self.expect_parse(rule)
			if not arg.keep:
				return ParserResult(None, False)

			if not self.more_tokens():
				raise ParserError("unexpected end of stream")
			elif self.get_token().tid == right:
				self.eat_token()
				return arg
			else:
				raise ParserError("unexpected token " + repr(self.get_token()))
				return ParserResult(None, False)
		else:
			return ParserResult(None, False)

	def parse_bound_list(self, rule, sep, left, right):
		if left is not None:
			self.expect_token(left)
		
		rtn = []
		while self.more_tokens():
			if self.get_token().tid == right:
				break
			rtn.append(self.expect_parse(rule))
			tok = self.get_token()
			if tok is None:
				raise ParserError("unexpected end of stream")
			elif tok.tid == sep:
				self.eat_token()
			elif tok.tid == right:
				break
			else:
				raise ParserError("unexpected token " + repr(self.get_token()))
			
		if right is not None:
			self.expect_token(right)

		return ParserResult([i.ast for i in rtn], True)

	def parse_unary_right(self, rhs_rule, base_rule, op_mapping):
		if not self.more_tokens():
			return ParserResult(None, False)

		for i in op_mapping:
			if self.get_token().tid == i[0]:
				tok = self.eat_token()

				rhs = self.expect_parse(rhs_rule)
				if rhs.keep:
					return ParserResult(ast.AST(
							tok,
							i[1],
							rhs = rhs.ast
						), True)
				else:
					return ParserResult(None, False)

		return self.try_parse(base_rule)

	def parse_unary_left(self, lhs_rule, op_mapping):
		lhs = self.try_parse(lhs_rule)
		if not lhs.keep:
			return ParserResult(None, False)

		while self.more_tokens():
			tok = self.get_token()

			matched = False
			for i in op_mapping:
				if tok.tid == i[0]:
					lhs.ast = ast.AST(tok, i[1], lhs = lhs.ast)
					matched = True
					break

			if matched:
				self.eat_token()
			else:
				break

		return lhs

	def parse_binary(self, lhs_rule, rhs_rule, op_mapping):
		lhs = self.try_parse(lhs_rule)
		if not lhs.keep:
			return ParserResult(None, False)

		if not self.more_tokens():
			return lhs

		tok = self.get_token()
		for i in op_mapping:
			if tok.tid == i[0]:
				self.eat_token()

				rhs = self.expect_parse(rhs_rule)

				return ParserResult(ast.AST(
						tok,
						i[1],
						lhs = lhs.ast,
						rhs = rhs.ast
					), True)

		return lhs

	def parse(self):
		raise NotImplementedError("please overload when you inherit from BaseParser")
