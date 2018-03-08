#include <whiskey/Messages/MessageContext.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Color.hpp>
#include <whiskey/Source/Source.hpp>

namespace whiskey {
void MessageContext::printSummary(std::ostream &os) const {
  if (warningCount > 0) {
    os << warningCount << " warning";
    if (warningCount != 1) {
      os << "s";
    }
  }

  if (warningCount > 0 && errorCount > 0) {
    os << ", ";
  }

  if (errorCount > 0) {
    os << errorCount << " error";
    if (errorCount != 1) {
      os << "s";
    }
  }

  if (warningCount > 0 || errorCount > 0) {
    os << ".\n";
  }
}

MessageContext::MessageContext() : tabWidth(2), warningCount(0), errorCount(0) {
}

void MessageContext::clear() {
  messages.clear();
  warningCount = 0;
  errorCount = 0;
}

void MessageContext::setTabWidth(unsigned int value) {
  tabWidth = value;
}

std::list<Message> &MessageContext::getMessages() {
  return messages;
}

const std::list<Message> &MessageContext::getMessages() const {
  return messages;
}

size_t MessageContext::getWarningCount() const {
  return warningCount;
}

size_t MessageContext::getErrorCount() const {
  return errorCount;
}

size_t MessageContext::getMessageCount() const {
  return messages.size();
}

std::ostream &MessageContext::describe() {
  return description;
}

void MessageContext::emit(Token token, Message::Severity severity) {
  Message message(token, severity, description.str());
  if (messages.empty()) {
    messages.push_back(message);
  } else {
    bool added = false;
    std::list<Message>::iterator last = messages.begin();
    for (std::list<Message>::iterator i = messages.begin(); i != messages.end(); i++) {
      if (message >= *i) {
        messages.insert(last, message);
        added = true;
        break;
      }
      last = i;
    }
    if (!added) {
      messages.push_back(message);
    }
  }

  description.str("");

  if (severity == Message::Severity::Warning) {
    warningCount++;
  } else if (severity >= Message::Severity::Error) {
    errorCount++;
  }
}

void MessageContext::emit(Message::Severity severity) {
  emit(Token(), severity);
}

void MessageContext::print(std::ostream &os, Source source) const {
  if (!messages.empty()) {
    source.setOffset(0);

    std::list<Message>::const_iterator iter = messages.cbegin();
    Token::LinenoType lineno = 1;

    while (source.more() && iter != messages.cend()) {
      if (lineno == iter->getToken().getLineno()) {
        iter->print(os, source);
        os << "\n";

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
            for (unsigned int i = 0; i < tabWidth; i++) {
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

    printSummary(os);

    W_ASSERT_TRUE(messages.empty() || iter == messages.cend(), "Must print all messages.");
  }

  W_ASSERT_LE(warningCount + errorCount, messages.size(), "Must print all messages.");
}

void MessageContext::print(std::ostream &os) const {
  if (!messages.empty()) {
    for (const Message &i : messages) {
      i.print(os);
      os << "\n";
    }

    os << "\n";
    printSummary(os);
  }

  W_ASSERT_LE(warningCount + errorCount, messages.size(), "Must print all messages.");
}
} // namespace whiskey
