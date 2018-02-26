#ifndef __WHISKEY_Core_Verbose_HPP
#define __WHISKEY_Core_Verbose_HPP

#include <ostream>

#define W_VERBOSE_PATH_MAXLEN 256

#ifdef W_ENABLE_VERBOSE
#define W_VERBOSE(desc) { \
	if (::whiskey::verbose) { \
		::whiskey::printVerbosePrefix(__FILE__, __LINE__, __FUNCTION__); \
		::whiskey::getVerboseOStream() << desc; \
		::whiskey::printVerboseSuffix(); \
	} \
}
#else
#define W_VERBOSE(desc)
#endif

namespace whiskey {
extern bool verbose;

std::ostream &getVerboseOStream();
void setVerboseOStream(std::ostream &os);

void printVerbosePrefix(const char *file, int line, const char *func);
void printVerboseSuffix();
}

#endif
