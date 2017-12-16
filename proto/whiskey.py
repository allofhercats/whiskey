#!/usr/bin/env python3.6

import sys

import cli
import base_lexer
import base_parser

import whiskey_lexer
import whiskey_parser

version_str = """Whiskey 0.1.0a"""

help_str = version_str + """

USAGE: whiskey [GLOBAL OPTIONS] <COMMAND> [COMMAND OPTIONS]

GLOBAL OPTIONS:
  -h|--help        Show this help.
  -V|--version     Show version info.
  --version-major  Get major version.
  --version-minor  Get minor version.
  --version-patch  Get patch version.
  -n|--dry         Disable all actual actions, just do a dry run.

COMMANDS:
  print            Print out information about a source file.
  cli              Start an interpreter instance.

COMMAND: print <*.w SOURCE>
  --tokens         Print out the list of tokens in the source file.
  --ast            Print out the AST of the source file."""

dry = False
was_command = False

i = 1
while i < len(sys.argv):
  if sys.argv[i] in ["-h", "--help"]:
    print(help_str)
    sys.exit(1)
  elif sys.argv[i] in ["-V", "--version"]:
    print(version_str)
    sys.exit(1)
  elif sys.argv[i] == "--version-major":
    print("0")
    sys.exit(1)
  elif sys.argv[i] == "--version-minor":
    print("1")
    sys.exit(1)
  elif sys.argv[i] == "--version-patch":
    print("0")
    sys.exit(1)
  elif sys.argv[i] in ["-n", "--dry"]:
    dry = True
  elif sys.argv[i] == "print":
    was_command = True
    i += 1

    sources = []
    show_tokens = False
    show_ast = False

    while i < len(sys.argv):
      if sys.argv[i] == "--tokens":
        show_tokens = True
      elif sys.argv[i] == "--ast":
        show_ast = True
      else:
        sources.append(sys.argv[i])
      i += 1

      for j in sources:
        text = ""
        try:
          file = open(j)
          text = file.read()
          file.close()
        except FileNotFoundError:
          print("error: unable to open "+repr(j))
          sys.exit(1)

        if show_tokens or show_ast:
          lexer = whiskey_lexer.WhiskeyLexer(text, j)

          try:
            lexer.lex()
          except base_lexer.LexingError as e:
            print("error:", e)

          if show_tokens:
            for k in lexer.tokens:
              print(k)

          if show_ast:
            parser = whiskey_parser.WhiskeyParser(lexer)

            res = None

            try:
              res = parser.parse()
            except base_parser.ParserError as e:
              print("error:", e)

            if res is not None:
              if res.keep:
                print(res.ast)
              else:
                print(None)
  elif sys.argv[i] == "cli":
    was_command = True
    i += 1
    if i < len(sys.argv):
      print("error: unknown argument " + repr(sys.argv[i]))
      sys.exit(1)

    cp = cli.CommandPrompt()
    cp.lexer_type = whiskey_lexer.WhiskeyLexer
    cp.parser_type = whiskey_parser.WhiskeyParser
    cp.echo_tokens = True
    cp.echo_ast = True
    cp.run()
  else:
    print("error: unknown argument " + repr(sys.argv[i]))
    sys.exit(1)
  i += 1

if not was_command:
  print("error: no command given")
  sys.exit(1)
