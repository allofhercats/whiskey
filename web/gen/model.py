import os
import pathlib

import token
import error
import lexing
import ast
import parsing
import config

def text_to_html(text):
	rtn = ""
	nlcount = 0

	for i in text:
		if i == '\n':
			nlcount += 1
			if nlcount == 2:
				rtn += "<p />\n\n"
		elif i == '\r':
			pass
		elif i == "<":
			rtn += "&lt;"
		elif i == ">":
			rtn += "&gt;"
		else:
			nlcount = 0
			rtn += i

	return rtn

def text_verbatim_to_html(cfg, text):
	rtn = ""

	tmp = text.strip("\n\r")
	pos = 0
	while pos < len(tmp):
		if tmp[pos] == " ":
			rtn += "&nbsp;"
		elif tmp[pos] == "\t":
			rtn += "&nbsp;" * cfg.html_tab_width
		elif tmp[pos] == "\n":
			rtn += "<br />"
		elif tmp[pos] == "<":
			rtn += "&lt;"
		elif tmp[pos] == ">":
			rtn += "&gt;"
		elif tmp[pos] == "\\" and pos+1 < len(tmp) and tmp[pos+1] == "!":
			rtn += "!"
			pos += 1
		else:
			rtn += tmp[pos]
		pos += 1

	return rtn

def ast_to_html(cfg, file, child):
	if child.aid == parsing.ASTID.TEXT:
		return text_to_html(child.text)
	elif child.aid == parsing.ASTID.TEXT_VERBATIM:
		return text_verbatim_to_html(cfg, child.text)
	elif child.aid == parsing.ASTID.COMMAND:
		if child.text == "b":
			rtn = "<b>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</b>"
			return rtn
		elif child.text == "i":
			rtn = "<i>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</i>"
			return rtn
		elif child.text == "u":
			rtn = "<u>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</u>"
			return rtn
		elif child.text == "st":
			rtn = "<del>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</del>"
			return rtn
		elif child.text == "code":
			rtn = "<p><code>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</code></p>"
			return rtn
		elif child.text == "verb":
			rtn = "<code>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</code>"
			return rtn
		elif child.text == "link":
			url = child.children[0].text.split(",")[0].strip()
			text = child.children[0].text.split(",")[1].strip()
			return "<a href='" + url + "'>" + text + "</a>"
		elif child.text == "dotted-list":
			rtn = "<ul>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</ul>"
			return rtn
		elif child.text == "numbered-list":
			rtn = "<ol>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</ol>"
			return rtn
		elif child.text == "item":
			rtn = "<li>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</li>"
			return rtn
		elif child.text == "table":
			rtn = "<table>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</table>"
			return rtn
		elif child.text == "row":
			rtn = "<tr>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</tr>"
			return rtn
		elif child.text == "heading":
			rtn = "<th>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</th>"
			return rtn
		elif child.text == "entry":
			rtn = "<td>"
			for i in child.children:
				rtn += ast_to_html(cfg, file, i)
			rtn += "</td>"
			return rtn
		elif child.text == "ref":
			r = File._refs[child.children[0].text]
			if r.file.path == file.path:
				return "<a href='#toc_" + str(r.toc_item.uid) + "'>" + r.toc_item.name + "</a>"
			else:
				return "<a href='" + file.get_rel_href(r.file) + "#toc_" + str(r.toc_item.uid) + "'>" + r.toc_item.name + "</a>"
		elif child.text == "tab-width":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_tab_width = int(body)
		elif child.text == "head":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_head = body
		elif child.text == "body-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_pre = body
		elif child.text == "body-nav-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_pre = body
		elif child.text == "body-nav-prev-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_prev_pre = body
		elif child.text == "body-nav-prev-name":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_prev_name = body
		elif child.text == "body-nav-prev-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_prev_post = body
		elif child.text == "body-nav-parent-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_parent_pre = body
		elif child.text == "body-nav-parent-name":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_parent_name = body
		elif child.text == "body-nav-parent-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_parent_post = body
		elif child.text == "body-nav-next-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_next_pre = body
		elif child.text == "body-nav-next-name":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_next_name = body
		elif child.text == "body-nav-next-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_next_post = body
		elif child.text == "body-nav-children-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_children_pre = body
		elif child.text == "body-nav-children-sep":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_children_sep = body
		elif child.text == "body-nav-children-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_children_post = body
		elif child.text == "body-nav-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_nav_post = body
		elif child.text == "body-wrapper-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_pre = body
		elif child.text == "body-wrapper-title-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_title_pre = body
		elif child.text == "body-wrapper-title-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_title_post = body
		elif child.text == "body-wrapper-subtitle-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_subtitle_pre = body
		elif child.text == "body-wrapper-subtitle-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_subtitle_post = body
		elif child.text == "body-wrapper-author-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_author_pre = body
		elif child.text == "body-wrapper-author-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_author_post = body
		elif child.text == "body-wrapper-date-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_date_pre = body
		elif child.text == "body-wrapper-date-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_date_post = body
		elif child.text == "body-wrapper-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_wrapper_post = body
		elif child.text == "body-toc-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_toc_pre = body
		elif child.text == "body-toc-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_toc_post = body
		elif child.text == "body-content-pre":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_content_pre = body
		elif child.text == "body-content-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_content_post = body
		elif child.text == "body-post":
			body = ""
			for i in child.children:
				body += ast_to_html(cfg, file, i)
			cfg.html_body_post = body
		else:
			error.emit_token_error(child.token, "unknown command " + repr(child.text))
	else:
		raise NotImplementedError("unsupported AST ID")

class TOCItem(object):
	_uid_counter = 0

	def __init__(self, name, level):
		self.uid = TOCItem._uid_counter
		TOCItem._uid_counter += 1
		self.name = name
		self.level = level

class Reference(object):
	def __init__(self, toc_item, file):
		self.toc_item = toc_item
		self.file = file

class File(object):
	_already_generated = []
	_already_loaded = []
	_refs = {}

	def __init__(self, path):
		self.path = path
		self.title = ""
		self.subtitle = ""
		self.author = ""
		self.date = ""

		self.prefix = os.path.splitext(os.path.basename(path))[0]

		self.parent = None
		self.prev = None
		self.next = None
		self.children = []

		self.toc = []

		self.content = []

		self.is_loaded = False

	def get_dir(self):
		return os.path.abspath(os.path.dirname(self.path))

	def get_html_filename(self):
		return os.path.splitext(os.path.basename(self.path))[0] + ".html"

	def get_rel_href(self, other):
		self_dir = self.get_dir()
		other_dir = other.get_dir()
		rel_dir = os.path.relpath(other_dir, self_dir)
		return os.path.join(rel_dir, other.get_html_filename())

	def load(self, cfg):
		if cfg.debug_loading:
			print("[-vloading] Loading " + repr(self.path) + "...")

		if self.path in File._already_loaded:
			raise ValueError("cyclic child")
		else:
			File._already_loaded.append(self.path)

		f = open(self.path, "r")
		text = f.read()

		lexer = lexing.Lexer(text, self.path)
		lexer.lex(cfg)
		parser = parsing.Parser(lexer)
		parser.parse(cfg)

		for i in parser.children:
			if i.aid == parsing.ASTID.COMMAND:
				if i.text == "title":
					for j in i.children:
						self.title += ast_to_html(cfg, self, j)
				elif i.text == "subtitle":
					for j in i.children:
						self.subtitle += ast_to_html(cfg, self, j)
				elif i.text == "author":
					for j in i.children:
						self.author += ast_to_html(cfg, self, j)
				elif i.text == "date":
					for j in i.children:
						self.date += ast_to_html(cfg, self, j)
				elif i.text == "load":
					tmp = File(os.path.join(self.get_dir(), i.children[0].text))
					if len(self.children) > 0:
						self.children[-1].next = tmp
						tmp.prev = self.children[-1]
					tmp.parent = self
					self.children.append(tmp)
				elif i.text in ["h1", "h2", "h3", "h4", "h5", "h6"]:
					level = int(i.text[1:])
					name = ""
					for j in i.children:
						name += ast_to_html(cfg, self, j)
					item = TOCItem(name, level)
					self.toc.append(item)
					self.content.append(i)
				elif i.text == "label":
					if len(self.toc) > 0:
						File._refs[i.children[0].text] = Reference(self.toc[-1], self)
					else:
						error.emit_token_error(child.token, "labels can only be placed after headings")
				else:
					self.content.append(i)
			else:
				self.content.append(i)

		self.is_loaded = True

		for i in self.children:
			i.load(cfg)

	def _gen_html(self, cfg):
		html_content = ""

		toc_counter = 0

		for i in self.content:
			if i.aid == parsing.ASTID.COMMAND and i.text in ["h1", "h2", "h3", "h4", "h5", "h6"]:
				level = int(i.text[1:])
				html_content += "<a name='toc_" + str(self.toc[toc_counter].uid) + "'></a>"
				html_content += "<h" + str(level) + ">" + self.toc[toc_counter].name + "</h" + str(level) + ">"
				toc_counter += 1
			else:
				html_content += ast_to_html(cfg, self, i)

		rtn = "<!DOCTYPE html>\n"
		rtn = "<html>"
		rtn += "<head>"
		rtn += "<title>" + self.title + "</title>"
		rtn += cfg.html_head
		rtn += "</head>"
		rtn += "<body>"
		rtn += cfg.html_body_pre
		rtn += "<div id='nav'>"
		rtn += cfg.html_body_nav_pre
		rtn += cfg.html_body_nav_prev_pre
		if self.prev is not None:
			rtn += "<a id='nav-prev' href='" + self.get_rel_href(self.prev) + "'>" + cfg.html_body_nav_prev_name + "</a>"
		rtn += cfg.html_body_nav_prev_post
		rtn += cfg.html_body_nav_parent_pre
		if self.parent is not None:
			rtn += "<a id='nav-parent' href='" + self.get_rel_href(self.parent) + "'>" + cfg.html_body_nav_parent_name + "</a>"
		rtn += cfg.html_body_nav_parent_post
		rtn += cfg.html_body_nav_next_pre
		if self.next is not None:
			rtn += "<a id='nav-next' href='" + self.get_rel_href(self.next) + "'>" + cfg.html_body_nav_next_name + "</a>"
		rtn += cfg.html_body_nav_next_post
		rtn += cfg.html_body_nav_post
		rtn += "<div id='nav-children'>"
		rtn += cfg.html_body_nav_children_pre
		first = True
		for i in self.children:
			if len(i.title) > 0:
				if first:
					first = False
				else:
					rtn += cfg.html_body_nav_children_sep
				rtn += "<a id='nav-child' href='" + self.get_rel_href(i) + "'>"
				rtn += i.title
				rtn += "</a>"
		rtn += cfg.html_body_nav_children_post
		rtn += "</div>"
		rtn += cfg.html_body_nav_post
		rtn += "</div>"
		rtn += "<div id='wrapper'>"
		rtn += cfg.html_body_wrapper_pre
		rtn += cfg.html_body_wrapper_title_pre
		if len(self.title) > 0:
			rtn += "<p id='title'>" + self.title + "</p>"
		rtn += cfg.html_body_wrapper_title_post
		rtn += cfg.html_body_wrapper_subtitle_pre
		if len(self.subtitle) > 0:
			rtn += "<p id='subtitle'>" + self.subtitle + "</p>"
		rtn += cfg.html_body_wrapper_subtitle_post
		rtn += cfg.html_body_wrapper_author_pre
		if len(self.author) > 0:
			rtn += "<p id='author'>" + self.author + "</p>"
		rtn += cfg.html_body_wrapper_author_post
		rtn += cfg.html_body_wrapper_date_pre
		if len(self.date) > 0:
			rtn += "<p id='date'>" + self.date + "</p>"
		rtn += cfg.html_body_wrapper_date_post
		rtn += cfg.html_body_wrapper_post
		rtn += "</div>"
		rtn += "<div id='toc'>"
		rtn += cfg.html_body_toc_pre
		current_level = 0
		for i in self.toc:
			while current_level < i.level:
				rtn += "<ul>"
				current_level += 1
			rtn += "<li><a href='#toc_" + str(i.uid) + "'>" + i.name + "</a></li>"
			while current_level > i.level:
				rtn += "</ul>"
				current_level -= 1
		while current_level > 0:
				rtn += "</ul>"
				current_level -= 1
		rtn += cfg.html_body_toc_post
		rtn += "</div>"
		rtn += "<div id='content'>"
		rtn += cfg.html_body_content_pre
		rtn += html_content
		rtn += cfg.html_body_content_post
		rtn += "</div>"
		rtn += cfg.html_body_post
		rtn += "</body>"
		rtn += "</html>"
		return rtn

	def gen(self, cfg):
		source_dir = os.path.dirname(self.path)
		source_reldir = os.path.relpath(source_dir, cfg.base_path)
		output_dir = os.path.join(cfg.build_path, source_reldir)
		output_path = os.path.join(output_dir, self.prefix + ".html")

		if cfg.debug_generating:
			print("[-vgenerating] Generating " + repr(output_path) + "...")

		if self.path in File._already_generated:
			error.emit_error(self.path, -1, "files cannot be loaded multiple times")
		else:
			File._already_generated.append(self.path)

		for i in self.children:
			i.gen(cfg)

		pathlib.Path(output_dir).mkdir(parents = True, exist_ok = True)

		html = self._gen_html(cfg)

		f = open(output_path, "w")
		f.write(html)
		f.close()
