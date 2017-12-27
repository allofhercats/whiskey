#!/usr/bin/env python3

from utils import *

total = 0

for i in list_files():
	f = open(i, "r")
	while True:
		c = f.read(1)
		if c == '\n':
			total += 1
		elif len(c) == 0:
			break
	f.close()

print(total)
