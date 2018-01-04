// #include "Module.inc"

#include <whiskey/Messages/Message.hpp>

#include <whiskey/Core/Color.hpp>
#include <whiskey/Core/Assert.hpp>

namespace whiskey {
Message::Severity Message::getSeverity(Message::ID id) {
  switch (id) {
  case CannotOpen:
    return FatalError;
  case UnexpectedChar:
    return Error;
  case MismatchedBlockComments:
    return Error;
  case ExclamationPointAlone:
    return Error;
  case MismatchedSingleQuotes:
    return Error;
  case MismatchedDoubleQuotes:
    return Error;
  case UnexpectedToken:
    return Error;
  default:
    W_ASSERT_UNREACHABLE("Unsupported message ID " << (int)id << ".");
  }
}

Message::Message(Range range, Message::ID id, std::string desc)
    : range(range), id(id), desc(desc) {
}

Range &Message::getRange() {
  return range;
}

const Range &Message::getRange() const {
  return range;
}

void Message::setRange(Range value) {
  range = value;
}

Message::ID Message::getID() const {
  return id;
}

void Message::setID(Message::ID value) {
  id = value;
}

const std::string &Message::getDesc() const {
  return desc;
}

void Message::setDesc(std::string value) {
  desc = value;
}

void Message::print(std::ostream &os) const {
  if (range.getStart().hasPath()) {
    os << range.getStart().getPath() << ":";
    if (range.getStart().hasLine()) {
      os << range.getStart().getLine() << ":";
      if (range.getStart().hasColumn()) {
        os << range.getStart().getColumn() << ":";
      }
    }
    os << " ";
  }

  switch (getSeverity(id)) {
  case Note:
    os << Color::greyDark << "note: ";
    break;
  case Warning:
    os << Color::yellowLight << "warning: ";
    break;
  case Error:
    os << Color::redLight << "error: ";
    break;
  case FatalError:
    os << Color::redLight << "fatal error: ";
    break;
  case InternalCompilerError:
    os << Color::magentaLight << "internal compiler error: ";
    break;
  default:
    W_ASSERT_UNREACHABLE("Unsupported severity " << (int)getSeverity(id)
                                                 << ".");
  }

  os << Color::reset << desc << "\n";
}
} // namespace whiskey
