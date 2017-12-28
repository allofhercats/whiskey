#ifndef __WHISKEY_Messages_MessageBuffer_HPP
#define __WHISKEY_Messages_MessageBuffer_HPP

#include <whiskey/Messages/Module.inc>

#include <whiskey/Messages/Message.hpp>

namespace whiskey {
class MessageBuffer {
private:
  std::vector<Message> messages;
  std::stringstream ss;
  unsigned int nWarnings;
  unsigned int nErrors;

public:
  MessageBuffer();
  MessageBuffer(const MessageBuffer &) = delete;

  std::vector<Message> &getMessages();
  const std::vector<Message> &getMessages() const;

  unsigned int getNWarnings() const;
  unsigned int getNErrors() const;
  unsigned int getNMessages() const;

  std::ostream &describe();
  void emit(Range range, Message::ID id);
  void emit(Location loc, Message::ID id);
  void emit(const Source &source, Message::ID id);
  void emit(Message::ID id);

  void print(std::ostream &os) const;
};
} // namespace whiskey

#endif
