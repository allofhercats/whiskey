#include <whiskey/Core/Assert.hpp>

#include <iostream>

namespace whiskey {
namespace {
std::ostream *assertOStream = nullptr;
}

std::ostream &getAssertOStream() {
  if (assertOStream == nullptr) {
    assertOStream = &std::cerr;
  }

  return *assertOStream;
}

void setAssertOStream(std::ostream &os) {
  assertOStream = &os;
}

void printAssertPrefix(const char *file, unsigned int line) {
  getAssertOStream() << file << ":" << std::dec << line << ": assertion failed: ";
}

void printAssertSuffix(const char *requirement) {
  getAssertOStream() << "\n  required: " << requirement << "\n";
}

void dieOnAssertFail() {
	getAssertOStream().flush();
  abort();
}
}
