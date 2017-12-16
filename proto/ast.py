class AST(object):
	TAB_WIDTH = 2

	def __init__(self, token, aid, **kwargs):
		if token is None:
			raise ValueError("token cannot be EOF")

		self.token = token
		self.aid = aid
		self.fields = kwargs

	def __getitem__(self, key):
		return self.fields[key]

	def __setitem__(self, key, value):
		self.fields[key] = value

	def __delitem__(self, key):
		del self.fields[key]

	def __len__(self):
		return len(self.fields)

	def __contains__(self, key):
		return key in self.fields

	def clear(self):
		self.fields.clear()

	def keys(self):
		return self.fields.keys()

	def values(self):
		return self.fields.values()

	def items(self):
		return self.fields.items()

	def __repr__(self):
		return "AST(" + repr(self.token) + ", " + str(self.aid) + ", ...)"

	def __str__(self):
		def helper(self, indent):
			rtn = str(self.aid) + " (" + self.token.path + ":" + str(self.token.lineno) + ":" + str(self.token.columnno) + ")"
			for i in self.fields.keys():
				rtn += "\n"
				rtn += " " * ((indent + 1) * AST.TAB_WIDTH)
				rtn += i + ": "
				if isinstance(self.fields[i], AST):
					rtn += helper(self.fields[i], indent+1)
				elif type(self.fields[i]) == list:
					n = 0
					for j in self.fields[i]:
						rtn += "\n"
						rtn += " " * ((indent + 2) * AST.TAB_WIDTH)
						rtn += "[" + str(n) + "] "
						if isinstance(j, AST):
							rtn += helper(j, indent+2)
						else:
							rtn += repr(j)
						n += 1
				else:
					rtn += repr(self.fields[i])
			return rtn

		return helper(self, 0)
