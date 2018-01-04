// #include "Module.inc"

#include <whiskey/Core/Color.hpp>

namespace whiskey {
bool Color::enabled = true;

Color::Color(const char *text) : text(text) {
}

const Color Color::reset("\033[39m");
const Color Color::red("\033[31m");
const Color Color::green("\033[32m");
const Color Color::yellow("\033[33m");
const Color Color::blue("\033[34m");
const Color Color::magenta("\033[35m");
const Color Color::cyan("\033[36m");
const Color Color::greyLight("\033[37m");
const Color Color::greyDark("\033[90m");
const Color Color::redLight("\033[91m");
const Color Color::greenLight("\033[92m");
const Color Color::yellowLight("\033[93m");
const Color Color::blueLight("\033[94m");
const Color Color::magentaLight("\033[95m");
const Color Color::cyanLight("\033[96m");
const Color Color::white("\033[97m");

void Color::print(std::ostream &os) const {
  if (enabled) {
    os << text;
  }
}

std::ostream &operator<<(std::ostream &os, const Color &value) {
  value.print(os);
  return os;
}
} // namespace whiskey
