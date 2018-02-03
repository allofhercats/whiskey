#include <whiskey/Messages/MessageContext.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Color.hpp>
#include <whiskey/Source/Source.hpp>

namespace whiskey {
MessageContext::MessageContext() : warningCount(0), errorCount(0) {
}

std::set<Message> &MessageContext::getMessages() {
  return messages;
}

const std::set<Message> &MessageContext::getMessages() const {
  return messages;
}

MessageContext::CountType MessageContext::getWarningCount() const {
  return warningCount;
}

MessageContext::CountType MessageContext::getErrorCount() const {
  return errorCount;
}

MessageContext::CountType MessageContext::getMessageCount() const {
  return messages.size();
}

std::ostream &MessageContext::describe() {
  return description;
}

void MessageContext::emit(Token token, Message::Severity severity) {
  messages.insert(Message(token, severity, description.str()));
  description.str("");
}

void MessageContext::emit(Message::Severity severity) {
  emit(Token(), severity);
}

void MessageContext::print(std::ostream &os, Source source) const {
  source.setOffset(0);

  std::set<Message>::const_iterator iter = messages.cbegin();
  Token::LinenoType lineno = 1;

  while (source.more() && iter != messages.cend()) {
    if (lineno == iter->getToken().getLineno()) {
      Token::ColumnnoType columnno = 1;
      int before = 0;
      int within = 0;
      bool isWithin = false;
      bool isAfter = false;

      while (source.more() && source.get() != '\n') {
        char chr = source.eat();

        if (!isWithin && columnno >= iter->getToken().getColumnno()) {
          isWithin = true;
          os << Color::green;
        }

        if (chr == '\t') {
          for (int i = 0; i < tabWidth; i++) {
            os << ' ';
          }
          if (!isAfter) {
            if (isWithin) {
              within += tabWidth;
            } else {
              before += tabWidth;
            }
          }
        } else {
          os << chr;
          if (!isAfter) {
            if (isWithin) {
              within++;
            } else {
              before++;
            }
          }
        }

        if ((isWithin && !isAfter) && columnno >= iter->getToken().getColumnno() + iter->getToken().getLength()) {
          isAfter = true;
          os << Color::reset;
        }

        columnno++;
      }

      os << '\n';

      for (int i = 0; i < before; i++) {
        os << ' ';
      }

      os << Color::greenLight;

      for (int i = 0; i < within; i++) {
        os << '^';
      }

      os << Color::reset << '\n';
      source.eat();
      iter++;
    } else {
      while (source.more() && source.eat() != '\n');
      lineno++;
    }
  }

  W_ASSERT_TRUE(iter == messages.cend(), "Must print all messages.");

  if (warningCount > 0) {
    os << warningCount << "warning";
    if (warningCount != 1) {
      os << "s";
    }
  }

  if (warningCount > 0 && errorCount > 0) {
    os << ", ";
  }

  if (errorCount > 0) {
    os << errorCount << "error";
    if (errorCount != 1) {
      os << "s";
    }
  }

  if (warningCount > 0 || errorCount > 0) {
    os << ".\n";
  }
}
} // namespace whiskey
