import os
import sys

def _get_project_root():
	tmp = os.path.abspath(os.path.dirname(__file__))
	while len(tmp) > 0:
		names = os.listdir(tmp)

		has_all_names = True
		for i in ["scripts", "include", "lib", "test", "CMakeLists.txt"]:
			if not os.path.exists(os.path.join(tmp, i)):
				has_all_names = False
				break

		if has_all_names:
			return tmp
		else:
			tmp = os.path.dirname(tmp)

	raise RuntimeError("Unable to detect project root.")

PROJECT_ROOT = _get_project_root()
SOURCE_DIRS_CXX = [
	os.path.join(PROJECT_ROOT, "include"),
	os.path.join(PROJECT_ROOT, "lib"),
	os.path.join(PROJECT_ROOT, "test", "demo"),
	os.path.join(PROJECT_ROOT, "test", "feature"),
	os.path.join(PROJECT_ROOT, "test", "fuzz"),
	os.path.join(PROJECT_ROOT, "test", "integration"),
	os.path.join(PROJECT_ROOT, "test", "unit")
]
SOURCE_DIRS_PYTHON = [
	os.path.join(PROJECT_ROOT, "proto"),
	os.path.join(PROJECT_ROOT, "scripts"),
	os.path.join(PROJECT_ROOT, "web", "gen"),
	os.path.join(PROJECT_ROOT, "web", "source")
]
SOURCE_DIRS_CMAKE = [
	PROJECT_ROOT
]

def list_files(language = "all"):
	if language == "c++":
		for sourcedir in SOURCE_DIRS_CXX:
			for dirpath, dirnames, filenames in os.walk(sourcedir):
				for filename in filenames:
					if os.path.splitext(filename)[1] in [".hpp", ".tpp", ".cpp"]:
						yield(os.path.join(dirpath, filename))
	elif language == "python":
		for sourcedir in SOURCE_DIRS_PYTHON:
			for dirpath, dirnames, filenames in os.walk(sourcedir):
				for filename in filenames:
					if os.path.splitext(filename)[1] in [".py"]:
						yield(os.path.join(dirpath, filename))
	elif language == "cmake":
		yield(os.path.join(PROJECT_ROOT, "CMakeLists.txt"))
	elif language == "all":
		for i in list_files("c++"):
			yield(i)
		for i in list_files("python"):
			yield(i)
		for i in list_files("cmake"):
			yield(i)
	else:
		raise RuntimeError("Unknown language (available: 'c++', 'python', 'cmake')")
