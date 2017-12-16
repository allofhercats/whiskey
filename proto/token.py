class Token(object):
	def __init__(self, path, lineno, columnno, offset, tid, text):
		self.path = path
		self.lineno = lineno
		self.columnno = columnno
		self.offset = offset
		self.tid = tid
		self.text = text

	def __repr__(self):
		return "Token(" + repr(self.path) + ", " + str(self.lineno) + ", " + str(self.columnno) + ", " + str(self.offset) + ", " + str(self.tid) + ", " + repr(self.text) + ")"
