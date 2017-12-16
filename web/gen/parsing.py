import enum

import token
import error
import lexing
import ast

@enum.unique
class ASTID(enum.Enum):
	TEXT = enum.auto()
	TEXT_VERBATIM = enum.auto()
	COMMAND = enum.auto()

class Parser(object):
	def __init__(self, lexer):
		self.lexer = lexer
		self.toks = []
		self.children = []

	def _parse_one(self, pos):
		if pos >= len(self.toks):
			return None

		if self.toks[pos].tid == lexing.TokenID.TEXT:
			return ast.AST(ASTID.TEXT, self.toks[pos].text), pos + 1
		elif self.toks[pos].tid == lexing.TokenID.TEXT_VERBATIM:
			return ast.AST(ASTID.TEXT_VERBATIM, self.toks[pos].text), pos + 1
		elif self.toks[pos].tid == lexing.TokenID.END:
			error.emit_token_error(self.toks[pos], "unexpected }")
		elif self.toks[pos].tid == lexing.TokenID.BEGIN:
			cmd = self.toks[pos].text
			pos += 1
			args = []
			while pos < len(self.toks) and self.toks[pos].tid != lexing.TokenID.END:
				if self.toks[pos].tid == lexing.TokenID.END:
					break
				arg, pos = self._parse_one(pos)
				if not (arg.aid == ASTID.TEXT and len(arg.text) == 0):
					args.append(arg)
			if pos >= len(self.toks) or self.toks[pos].tid != lexing.TokenID.END:
				error.emit_token_error(self.toks[pos if pos < len(self.toks) else -1], "{ expects closing }")
			return ast.AST(ASTID.COMMAND, cmd, *args), pos + 1
		else:
			raise NotImplementedError("unsupported token ID")

	def parse(self, cfg):
		def is_all_whitespace(text):
			for i in text:
				if not i in " \t\r\n":
					return False
			return True

		if len(self.toks) == 0:
			self.toks = self.lexer.toks

		pos = 0
		while pos < len(self.toks):
			child, pos = self._parse_one(pos)
			if cfg.debug_parsing:
				print("[-vparsing] Emitted " + repr(child))
			if child.aid == ASTID.TEXT:
				if not is_all_whitespace(child.text):
					self.children.append(child)
			elif child.aid == ASTID.TEXT_VERBATIM:
				if not is_all_whitespace(child.text):
					self.children.append(child)
			else:
				self.children.append(child)
