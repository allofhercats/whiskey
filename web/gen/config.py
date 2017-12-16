import os
import sys

import model

class Config(object):
	def __init__(self):
		self.debug_config = False
		self.debug_loading = False
		self.debug_lexing = False
		self.debug_parsing = False
		self.debug_generating = False
		self.index_path = ""
		self.base_path = ""
		self.build_path = ""
		self.html_tab_width = 2
		self.html_head = ""
		self.html_body_pre = ""
		self.html_body_nav_pre = ""
		self.html_body_nav_prev_pre = ""
		self.html_body_nav_prev_name = "Previous"
		self.html_body_nav_prev_post = ""
		self.html_body_nav_parent_pre = ""
		self.html_body_nav_parent_name = "Up"
		self.html_body_nav_parent_post = ""
		self.html_body_nav_next_pre = ""
		self.html_body_nav_next_name = "Next"
		self.html_body_nav_next_post = ""
		self.html_body_nav_children_pre = ""
		self.html_body_nav_children_sep = ""
		self.html_body_nav_children_post = ""
		self.html_body_nav_post = ""
		self.html_body_wrapper_pre = ""
		self.html_body_wrapper_title_pre = ""
		self.html_body_wrapper_title_post = ""
		self.html_body_wrapper_subtitle_pre = ""
		self.html_body_wrapper_subtitle_post = ""
		self.html_body_wrapper_author_pre = ""
		self.html_body_wrapper_author_post = ""
		self.html_body_wrapper_date_pre = ""
		self.html_body_wrapper_date_post = ""
		self.html_body_wrapper_post = ""
		self.html_body_toc_pre = ""
		self.html_body_toc_post = ""
		self.html_body_content_pre = ""
		self.html_body_content_post = ""
		self.html_body_post = ""

	def parse(self, args):
		pos = 0

		while pos < len(args):
			if args[pos] == "-h" or args[pos] == "--help":
				print("Whiskey Doctext Generator 0.1.0a")
				print("Copyright 2017 Oliver Katz")
				print()
				print("usage: wdtgen [OPTIONS]")
				print()
				print("OPTIONS")
				print("  -h|--help         Show help.")
				print("  -V|--version      Show version.")
				print("  -i <INPUT *.wdt>  Specify input file.")
				print("  -o <OUTPUT DIR>   Specify output directory.")
				print("  -vno-loading")
				print("  -vloading         Enable/disable verbose messages for file loading.")
				print("  -vno-lexing")
				print("  -vlexing          Enable/disable verbose messages for lexing.")
				print("  -vno-parsing")
				print("  -vparsing         Enable/disable verbose messages for parsing.")
				print("  -vno-generating")
				print("  -vgenerating      Enable/disable verbose messages for generating.")
				print("  -vnone")
				print("  -vall             Enable/disable all verbose messages.")
				return False
			elif args[pos] == "-V" or args[pos] == "--version":
				print("Whiskey Doctext Generator 0.1.0a")
				print("Copyright 2017 Oliver Katz")
				return False
			elif args[pos] == "-i":
				pos += 1
				if pos >= len(args):
					print("error: -i expects argument")
					return False
				elif args[pos][0] == "-":
					print("error: -i expects argument")
					return False
				else:
					self.index_path = os.path.abspath(args[pos])
					self.base_path = os.path.dirname(self.index_path)
					pos += 1
			elif args[pos] == "-o":
				pos += 1
				if pos >= len(args):
					print("error: -o expects argument")
					return False
				elif args[pos][0] == "-":
					print("error: -o expects argument")
					return False
				else:
					self.build_path = os.path.abspath(args[pos])
					pos += 1
			elif args[pos] == "-vconfig":
				self.debug_config = True
				pos += 1
			elif args[pos] == "-vno-config":
				self.debug_config = False
				pos += 1
			elif args[pos] == "-vloading":
				self.debug_loading = True
				pos += 1
			elif args[pos] == "-vno-loading":
				self.debug_loading = False
				pos += 1
			elif args[pos] == "-vlexing":
				self.debug_lexing = True
				pos += 1
			elif args[pos] == "-vno-lexing":
				self.debug_lexing = False
				pos += 1
			elif args[pos] == "-vparsing":
				self.debug_parsing = True
				pos += 1
			elif args[pos] == "-vno-parsing":
				self.debug_parsing = False
				pos += 1
			elif args[pos] == "-vgenerating":
				self.debug_generating = True
				pos += 1
			elif args[pos] == "-vno-generating":
				self.debug_generating = False
				pos += 1
			elif args[pos] == "-vall":
				self.debug_config = True
				self.debug_loading = True
				self.debug_lexing = True
				self.debug_parsing = True
				self.debug_generating = True
				pos += 1
			elif args[pos] == "-vnone":
				self.debug_config = False
				self.debug_loading = False
				self.debug_lexing = False
				self.debug_parsing = False
				self.debug_generating = False
				pos += 1
			elif args[pos][0] == "-":
				print("error: unexpected argument", args[pos])
				return False
			else:
				print("error: unexpected argument", args[pos])
				return False

		if len(self.index_path) == 0:
			print("error: missing argument -i")
			return False

		if len(self.build_path) == 0:
			print("error: missing argument -o")
			return False

		if self.debug_config:
			print("[-vconfig] Index path is " + repr(self.index_path) + "...")
			print("[-vconfig] Base path is " + repr(self.base_path) + "...")
			print("[-vconfig] Build path is " + repr(self.build_path) + "...")

		return True

	def parse_args(self):
		return self.parse(sys.argv[1:])
