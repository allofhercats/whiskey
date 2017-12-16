class AST(object):
	def __init__(self, aid, text, *children):
		self.aid = aid
		self.text = text
		self.children = list(children)

	def __repr__(self):
		def helper(ast, indent):
			rtn = "AST(" + str(ast.aid) + ", " + repr(ast.text)
			if len(ast.children) > 0:
				for i in ast.children:
					rtn += ",\n"
					rtn += (" " * (indent+2))
					rtn += helper(i, indent+2)
				rtn += "\n" + (" " * indent) + ")"
			else:
				rtn += ")"
			return rtn

		return helper(self, 0)
