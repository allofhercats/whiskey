import atexit
import os
import readline

import base_lexer
import base_parser

class CommandPrompt(object):
	def __init__(self, prompt = "\033[0;90m%\033[0;0m "):
		self.prompt = prompt
		self.history_file = ".whiskey_history"
		self.running = True
		self.echo = False
		self.echo_tokens = False
		self.echo_ast = False
		self.lexer_type = None
		self.parser_type = None

	def lex_command(self, line):
		pos = 0
		buf = ""
		toks = []

		while pos < len(line):
			if line[pos] in " \t\r\n":
				if len(buf) > 0:
					toks.append(buf)
					buf = ""
				pos += 1
			elif line[pos] == "'":
				if len(buf) > 0:
					toks.append(buf)
					buf = ""
				buf += line[pos]
				pos += 1
				last = None
				while pos < len(line):
					if last != '\\' and line[pos] == '\'':
						break
					else:
						last = line[pos]
						buf += line[pos]
						pos += 1
				if pos >= len(line) or line[pos] != '\'':
					print("error: \' expects closing \'")
					return None
				buf += line[pos]
				pos += 1
				toks.append(buf)
				buf = ""
			elif line[pos] == "\"":
				if len(buf) > 0:
					toks.append(buf)
					buf = ""
				buf += line[pos]
				pos += 1
				last = None
				while pos < len(line):
					if last != '\\' and line[pos] == '\"':
						break
					else:
						last = line[pos]
						buf += line[pos]
						pos += 1
				if pos >= len(line) or line[pos] != '\"':
					print("error: \" expects closing \"")
					return None
				buf += line[pos]
				pos += 1
				toks.append(buf)
				buf = ""
			else:
				buf += line[pos]
				pos += 1

		if len(buf) > 0:
			toks.append(buf)

		return toks

	def run_command(self, line):
		toks = self.lex_command(line)
		if toks is None:
			return

		if len(toks) == 0:
			print("error: ':' alone is not a command")
			return

		if toks[0] == "quit":
			if len(toks) == 1:
				self.running = False
			else:
				print("error: command quit expects 0 arguments")
		elif toks[0] == "exit":
			if len(toks) == 1:
				self.running = False
			else:
				print("error: command exit expects 0 arguments")
		elif toks[0] == "echo":
			if len(toks) == 1:
				if self.echo:
					print("on")
				else:
					print("off")
			elif len(toks) == 2:
				if toks[1] == "on":
					self.echo = True
				elif toks[1] == "off":
					self.echo = False
				else:
					print("error: invalid value for echo " + repr(toks[1]))
					print("note: expected 'on' or 'off'")
			else:
				print("error: command echo expects 0 or 1 arguments")
		elif toks[0] == "echo-tokens":
			if len(toks) == 1:
				if self.echo_tokens:
					print("on")
				else:
					print("off")
			elif len(toks) == 2:
				if toks[1] == "on":
					self.echo_tokens = True
				elif toks[1] == "off":
					self.echo_tokens = False
				else:
					print("error: invalid value for echo-tokens " + repr(toks[1]))
					print("note: expected 'on' or 'off'")
			else:
				print("error: command echo-tokens expects 0 or 1 arguments")
		elif toks[0] == "echo-ast":
			if len(toks) == 1:
				if self.echo_ast:
					print("on")
				else:
					print("off")
			elif len(toks) == 2:
				if toks[1] == "on":
					self.echo_ast = True
				elif toks[1] == "off":
					self.echo_ast = False
				else:
					print("error: invalid value for echo-ast " + repr(toks[1]))
					print("note: expected 'on' or 'off'")
			else:
				print("error: command echo-ast expects 0 or 1 arguments")
		else:
			print("error: unknown command " + repr(toks[0]))

	def run(self):
		self.running = True

		history_path = os.path.join(os.path.expanduser("~"), self.history_file)
		try:
			readline.read_history_file(history_path)
			readline.set_history_length(1000)
		except FileNotFoundError:
			pass

		atexit.register(readline.write_history_file, history_path)

		while self.running:
			line = ""
			try:
				line = input(self.prompt)
			except EOFError:
				print(":quit")
				break
			except KeyboardInterrupt:
				print()
				continue

			line = line.strip()
			if len(line) > 0:
				if line[0] == ":":
					self.run_command(line[1:])
				else:
					if self.echo:
						print(line)

					if self.lexer_type is not None:
						lexer = self.lexer_type(line)

						try:
							lexer.lex()
						except base_lexer.LexingError as e:
							print("error:", e)

						if self.echo_tokens:
							for i in lexer.tokens:
								print(i)

						if self.parser_type is not None:
							parser = self.parser_type(lexer)

							res = None

							try:
								res = parser.parse()
							except base_parser.ParserError as e:
								print("error:", e)

							if self.echo_ast and res is not None:
								if res.keep:
									print(res.ast)
								else:
									print(None)