#!/usr/bin/env python3

import os

from utils import *

os.system("clang-format -i -style=file " + " ".join(list_files("c++")))
