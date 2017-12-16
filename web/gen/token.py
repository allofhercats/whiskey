class Token(object):
	def __init__(self, path, line, tid, text):
		self.path = path
		self.line = line
		self.tid = tid
		self.text = text

	def __repr__(self):
		return "Token(" + repr(self.path) + ", " + str(self.line) + ", " + str(self.tid) + ", " + repr(self.text) + ")"
