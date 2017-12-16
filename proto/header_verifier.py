import base_verifier

import whiskey_parser

class HeaderVerifier(object):
	def __init__(self):
		pass

	def verify(self, node):
		if node.aid == whiskey_parser.ASTID.PAGE:
			for i in node.fields["children"]:
				self.verify(i)
		elif node.aid == whiskey_parser.ASTID.TOPLEVEL_IMPORT: