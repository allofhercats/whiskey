#include <whiskey/Core/Assert.hpp>

#include <iostream>

#include <whiskey/Core/Color.hpp>

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

void printAssertMessage(const char *file, int line, const char *desc) {
  getAssertStream() << Color::reset << file << ":" << line << ": "
                    << Color::magentaLight
                    << "assertion failed: " << Color::white << desc
                    << Color::reset << "\n";
  getAssertStream().flush();
}

void printAssertReasonPre() {
  getAssertStream() << Color::greyLight << " reason: " << Color::reset;
  getAssertStream().flush();
}

void printAssertReasonPost() {
  getAssertStream() << "\n";
  getAssertStream().flush();
}

[[noreturn]] void dieOnAssertFail() {
  abort();
}

void printAssertValueBool(const char *label,
                          AssertBool value,
                          const char *text) {
  getAssertStream() << Color::greyLight << "  " << label << ": " << Color::reset
                    << text << "\n";
  getAssertStream() << "    which is: " << (value ? "true" : "false") << "\n";
  getAssertStream().flush();
}

void printAssertValuePointer(const char *label,
                             AssertPointer value,
                             const char *text) {
  getAssertStream() << Color::greyLight << "  " << label << ": " << Color::reset
                    << text << "\n";
  getAssertStream() << "    which is: " << value << "\n";
  getAssertStream().flush();
}

void printAssertValueInt(const char *label, AssertInt value, const char *text) {
  getAssertStream() << Color::greyLight << "  " << label << ": " << Color::reset
                    << text << "\n";
  getAssertStream() << "    which is: " << value << "\n";
  getAssertStream().flush();
}

void printAssertValueUInt(const char *label,
                          AssertUInt value,
                          const char *text) {
  getAssertStream() << Color::greyLight << "  " << label << ": " << Color::reset
                    << text << "\n";
  getAssertStream() << "    which is: " << value << "\n";
  getAssertStream().flush();
}
} // namespace whiskey
