#ifndef __WHISKEY_Core_Backtrace_HPP
#define __WHISKEY_Core_Backtrace_HPP

#include <string>
#include <ostream>

namespace whiskey {
std::string getCurrentBinaryName(int maxLength = 1024);
std::string getBinaryNameOfSymbol(void *symbol);
void printBacktrace(std::ostream &os, int maxDepth = 511);
} // namespace whiskey

#endif
