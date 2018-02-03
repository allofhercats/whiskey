#ifndef __WHISKEY_Messages_MessageContext_HPP
#define __WHISKEY_Messages_MessageContext_HPP

#include <sstream>
#include <set>

#include <whiskey/Messages/Message.hpp>

namespace whiskey {
class MessageContext {
public:
  typedef uint32_t CountType;
  typedef uint32_t TabWidthType;

private:
  TabWidthType tabWidth;
  std::set<Message> messages;
  std::stringstream description;
  CountType warningCount;
  CountType errorCount;

public:
  MessageContext();
  MessageContext(const MessageContext &) = delete;

  void clear();

  void setTabWidth(TabWidthType value);

  std::set<Message> &getMessages();
  const std::set<Message> &getMessages() const;

  CountType getWarningCount() const;
  CountType getErrorCount() const;
  CountType getMessageCount() const;

  std::ostream &describe();
  void emit(Token token, Message::Severity severity);
  void emit(Message::Severity severity);

  void print(std::ostream &os, Source source) const;
};
} // namespace whiskey

#endif
