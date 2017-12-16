import enum

import token
import error

@enum.unique
class TokenID(enum.Enum):
	TEXT = enum.auto()
	TEXT_VERBATIM = enum.auto()
	BEGIN = enum.auto()
	END = enum.auto()

class Lexer(object):
	def __init__(self, text, path = "--"):
		self.text = text
		self.path = path
		self.first_line = 1
		self.last_line = 1
		self.first_offset = 0
		self.last_offset = 0
		self.buf = ""
		self.toks = []

	def more_chrs(self):
		return self.last_offset < len(self.text)

	def get_chr(self, lookahead = 0):
		if self.last_offset + lookahead < len(self.text):
			return self.text[self.last_offset + lookahead]
		else:
			return None

	def eat_chr(self):
		rtn = self.get_chr()
		if not rtn is None:
			if rtn == "\n":
				self.last_line += 1
			self.last_offset += 1
			self.buf += rtn
			return rtn
		else:
			return None

	def skip_token(self):
		self.first_line = self.last_line
		self.first_offset = self.last_offset
		self.buf = ""

	def emit_token(self, tid, cfg):
		if cfg.debug_lexing:
			print("[-vlexing] Emitting token " + repr(self.buf.rstrip()) + " (" + str(tid) + ")...")
		self.toks.append(token.Token(self.path, self.first_line, tid, self.buf))
		self.skip_token()

	def has_token(self):
		return len(self.buf) > 0

	def lex(self, cfg):
		while self.more_chrs():
			if self.get_chr() == '\\':
				if self.has_token():
					self.emit_token(TokenID.TEXT, cfg)

				self.eat_chr()
				self.skip_token()

				if not self.more_chrs():
					if len(self.toks) > 0:
						error.emit_error(self.path, self.last_line, "unexpected end of stream")

				if self.get_chr() == '\\':
					self.eat_chr()
				elif self.get_chr() == '{':
					self.eat_chr()
				elif self.get_chr() == '}':
					self.eat_chr()
				else:
					if self.has_token():
						self.emit_token(TokenID.TEXT, cfg)

					while self.more_chrs() and self.get_chr() != '{':
						self.eat_chr()

					if not self.more_chrs():
						error.emit_error(self.path, self.last_line, "unexpected end of stream")
					elif self.get_chr() != '{':
						error.emit_error(self.path, self.last_line, "missing { after command")
					else:
						self.emit_token(TokenID.BEGIN, cfg)
						self.eat_chr()
						self.skip_token()
			elif self.get_chr() == '}':
				if self.has_token():
					self.emit_token(TokenID.TEXT, cfg)
				self.eat_chr()
				self.emit_token(TokenID.END, cfg)
			elif self.get_chr() == '!':
				if self.get_chr(1) == '{':
					if self.has_token():
						self.emit_token(TokenID.TEXT, cfg)
					last = None
					self.eat_chr()
					self.eat_chr()
					self.skip_token()
					while self.more_chrs():
						if last == '}' and self.get_chr() == '!':
							break
						else:
							last = self.eat_chr()
					if self.get_chr() != '!' or last != '}':
						error.emit_error(self.path, self.last_line, "!{ expects closing }!")
					self.eat_chr()
					self.buf = self.buf[:-2]
					self.emit_token(TokenID.TEXT_VERBATIM, cfg)
				else:
					self.eat_chr()
			else:
				self.eat_chr()

		if self.has_token():
			self.emit_token(TokenID.TEXT, cfg)
