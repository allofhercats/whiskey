#include <whiskey/Core/Assert.hpp>

#include <iostream>

#include <whiskey/Core/Backtrace.hpp>
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
  *assertStream << Color::reset << file << ":" << line << ": "
                << Color::magentaLight << "assertion failed: " << Color::white
                << desc << Color::reset << "\n";
}

void printAssertReasonPre() {
  *assertStream << Color::greyLight << " reason: " << Color::reset;
}

void printAssertReasonPost() {
  *assertStream << "\n";
}

[[noreturn]] void dieOnAssertFail() {
  printBacktrace(*assertStream);
  abort();
}

void printAssertValueBool(const char *label,
                          AssertBool value,
                          const char *text) {
  *assertStream << Color::greyLight << "  " << label << ": " << Color::reset
                << text << "\n";
  *assertStream << "    which is: " << (value ? "true" : "false") << "\n";
}

void printAssertValuePointer(const char *label,
                             AssertPointer value,
                             const char *text) {
  *assertStream << Color::greyLight << "  " << label << ": " << Color::reset
                << text << "\n";
  *assertStream << "    which is: " << value << "\n";
}

void printAssertValueInt(const char *label, AssertInt value, const char *text) {
  *assertStream << Color::greyLight << "  " << label << ": " << Color::reset
                << text << "\n";
  *assertStream << "    which is: " << value << "\n";
}

void printAssertValueUInt(const char *label,
                          AssertUInt value,
                          const char *text) {
  *assertStream << Color::greyLight << "  " << label << ": " << Color::reset
                << text << "\n";
  *assertStream << "    which is: " << value << "\n";
}
} // namespace whiskey
