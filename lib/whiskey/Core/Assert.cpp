#include "Module.inc"

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
namespace {
std::ostream *assertStream = nullptr;
}

std::ostream &getAssertStream() {
  if (assertStream == nullptr) {
    assertStream = &std::cerr;
  }

  return *assertStream;
}

void setAssertStream(std::ostream &os) {
  assertStream = &os;
}
} // namespace whiskey
