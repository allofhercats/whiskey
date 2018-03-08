#ifndef __WHISKEY_Messages_MessageContext_HPP
#define __WHISKEY_Messages_MessageContext_HPP

#include <sstream>
#include <list>

#include <whiskey/Messages/Message.hpp>

namespace whiskey {
class MessageContext {
private:
  unsigned int tabWidth;
  std::list<Message> messages;
  std::stringstream description;
  size_t warningCount;
  size_t errorCount;

  void printSummary(std::ostream &os) const;

public:
  MessageContext();
  MessageContext(const MessageContext &) = delete;

  void clear();

  void setTabWidth(unsigned int value);

  std::list<Message> &getMessages();
  const std::list<Message> &getMessages() const;

  size_t getWarningCount() const;
  size_t getErrorCount() const;
  size_t getMessageCount() const;

  std::ostream &describe();
  void emit(Token token, Message::Severity severity);
  void emit(Message::Severity severity);

  void print(std::ostream &os, Source source) const;
  void print(std::ostream &os) const;
};
} // namespace whiskey

#endif
