import os
import sys
import atexit

_n_errors = 0

def emit_error(path, line, *args):
	global _n_errors
	print(path + ":" + str(line) + ": error:", *args, file=sys.stderr)
	_n_errors += 1

def emit_token_error(token, *args):
	emit_error(token.path, token.line, *args)

def error_summary():
	global _n_errors
	if _n_errors == 1:
		print("1 error.")
	elif _n_errors > 1:
		print(_n_errors, "errors.")
	os._exit(1)

atexit.register(error_summary)
