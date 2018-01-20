#ifndef __WHISKEY_Core_Backtrace_HPP
#define __WHISKEY_Core_Backtrace_HPP

#include <ostream>
#include <string>

#define W_BACKTRACE_SKIP_FIRST 2

namespace whiskey {
std::string getCurrentBinaryName(int maxLength = 1024);
std::string getBinaryNameOfSymbol(void *symbol);
void printBacktrace(std::ostream &os, int maxDepth = 512 - W_BACKTRACE_SKIP_FIRST);
} // namespace whiskey

#endif
