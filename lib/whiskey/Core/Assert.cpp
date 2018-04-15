#include <whiskey/Core/Assert.hpp>

#include <map>
#include <iostream>

namespace whiskey {
namespace {
std::map<AssertMode, std::ostream *> assertOStreams;
std::map<AssertMode, size_t> assertFails;
}

const size_t assertModeCount = static_cast<size_t>(AssertMode::Last) - static_cast<size_t>(AssertMode::First) + 1;

std::ostream &getAssertOStream(AssertMode mode) {
	if (assertOStreams.find(mode) == assertOStreams.end()) {
		assertOStreams[mode] = nullptr;
	}

	if (assertOStreams[mode] == nullptr) {
    assertOStreams[mode] = &std::cerr;
  }

  return *assertOStreams[mode];
}

void setAssertOStream(AssertMode mode, std::ostream &os) {
	assertOStreams[mode] = &os;
}

size_t getNAssertFailures(AssertMode mode) {
	if (assertFails.find(mode) == assertFails.end()) {
		assertFails[mode] = 0;
	}

	return assertFails[mode];
}

void printAssertPrefix(AssertMode mode, const char *file, unsigned int line) {
  getAssertOStream(mode) << file << ":" << std::dec << line << ": ";
  switch (mode) {
  	case AssertMode::Internal:
  		getAssertOStream(mode) << "assertion failed: ";
  		break;
  	case AssertMode::Test:
  		getAssertOStream(mode) << "test assertion failed: ";
  		break;
  }
}

void printAssertSuffix(AssertMode mode, const char *requirement) {
  getAssertOStream(mode) << "\n  required: " << requirement << "\n";
}

void failAssertDie() {
	getAssertOStream(AssertMode::Internal).flush();
  abort();
}

void failAssert(AssertMode mode) {
	if (assertFails.find(mode) == assertFails.end()) {
		assertFails[mode] = 0;
	}

	++assertFails[mode];
}
}
