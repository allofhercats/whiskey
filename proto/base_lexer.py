import token

class LexingError(Exception):
	pass

class BaseLexer(object):
	def __init__(self, text, path = "--"):
		self.text = text
		self.path = path
		self.first_lineno = 1
		self.first_columnno = 1
		self.first_offset = 0
		self.last_lineno = 1
		self.last_columnno = 1
		self.last_offset = 0
		self.buffer = ""
		self.tokens = []

	def get_chr(self, lookahead = 0):
		if self.last_offset + lookahead < len(self.text):
			return self.text[self.last_offset + lookahead]
		else:
			return None

	def eat_chr(self):
		rtn = self.get_chr()
		if rtn is None:
			return None

		self.last_offset += 1
		if rtn == '\r':
			rtn = self.get_chr()
			if rtn == '\n':
				self.last_offset += 1
			self.last_lineno += 1
			self.last_columnno = 1
			self.buffer += '\n'
			return '\n'
		else:
			self.last_columnno += 1

		self.buffer += rtn
		return rtn

	def more_chrs(self):
		return self.last_offset < len(self.text)

	def emit_token(self, tid):
		self.tokens.append(token.Token(self.path, self.first_lineno, self.first_columnno, self.first_offset, tid, self.buffer))
		self.skip_token()

	def skip_token(self):
		self.first_lineno = self.last_lineno
		self.first_columnno = self.last_columnno
		self.first_offset = self.last_offset
		self.buffer = ""

	def get_text(self):
		return self.buffer

	def lex(self):
		raise NotImplementedError("please overload when you inherit BaseLexer")
