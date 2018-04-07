#include <whiskey-testing/PathUtils.hpp>

#include <string.h>
#include <libgen.h>

namespace whiskey {
namespace pathutils {
std::string concat(const std::string &base, const std::string &name) {
	char buffer[W_PATH_BUFFER_SIZE];
	sprintf(buffer, "%s%s%s", base.c_str(), W_PATH_SEPARATOR, name.c_str());
	return buffer;
}

std::string dirname(const std::string &path) {
	char buffer[W_PATH_BUFFER_SIZE];
	strncpy(buffer, path.c_str(), path.size());
	return ::dirname(buffer);
}

#pragma clang diagnostic ignored "-Wmissing-prototypes"
char *_basenameWrapper(char *path) {
	return basename(path);
}

#undef basename
std::string basename(const std::string &path) {
	char buffer[W_PATH_BUFFER_SIZE];
	strncpy(buffer, path.c_str(), path.size());
	return _basenameWrapper(buffer);
}

void splitext(const std::string &path, std::string &name, std::string &ext) {
	std::string bn = basename(path);
	std::string::size_type index = bn.find(".");
	if (index == std::string::npos) {
		name = bn;
		ext = "";
	} else {
		name = bn.substr(0, index);
		ext = bn.substr(index);
	}
}
}
}
