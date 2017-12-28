#include "Module.inc"

#include <whiskey/Messages/MessageBuffer.hpp>

namespace whiskey {
MessageBuffer::MessageBuffer() : nWarnings(0), nErrors(0) {
}

std::vector<Message> &MessageBuffer::getMessages() {
  return messages;
}

const std::vector<Message> &MessageBuffer::getMessages() const {
  return messages;
}

unsigned int MessageBuffer::getNWarnings() const {
  return nWarnings;
}

unsigned int MessageBuffer::getNErrors() const {
  return nErrors;
}

unsigned int MessageBuffer::getNMessages() const {
  return messages.size();
}

std::ostream &MessageBuffer::describe() {
  return ss;
}

void MessageBuffer::emit(Range range, Message::ID id) {
  Message tmp = Message(range, id, ss.str());
  ss.str("");
  messages.push_back(tmp);
}

void MessageBuffer::emit(Location loc, Message::ID id) {
  emit(Range(loc), id);
}

void MessageBuffer::emit(const Source &source, Message::ID id) {
  emit(Range(Location(source)), id);
}

void MessageBuffer::emit(Message::ID id) {
  emit(Range(), id);
}

void MessageBuffer::print(std::ostream &os) const {
  for (const Message &i : messages) {
    i.print(os);
  }

  if (nWarnings > 0) {
    os << nWarnings << "warning";
    if (nWarnings != 1) {
      os << "s";
    }
  }

  if (nWarnings > 0 && nErrors > 0) {
    os << ", ";
  }

  if (nErrors > 0) {
    os << nErrors << "error";
    if (nErrors != 1) {
      os << "s";
    }
  }

  if (nWarnings > 0 || nErrors > 0) {
    os << ".\n";
  }
}
} // namespace whiskey
