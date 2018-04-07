#ifndef __WHISKEY_TEST_PathUtils_HPP
#define __WHISKEY_TEST_PathUtils_HPP

#include <string>

#define W_PATH_BUFFER_SIZE 4096
#define W_PATH_SEPARATOR "/"

namespace whiskey {
namespace pathutils {
std::string concat(const std::string &base, const std::string &name);
std::string dirname(const std::string &path);
std::string basename(const std::string &path);
void splitext(const std::string &path, std::string &name, std::string &ext);
}
}

#endif
