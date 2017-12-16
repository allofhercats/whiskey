#!/usr/bin/env python3.6

import os

import config
import model

c = config.Config()
if not c.parse_args():
	os._exit(1)

f = model.File(c.index_path)
f.load(c)
f.gen(c)

os._exit(0)
