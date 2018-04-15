#ifndef __WHISKEY_AST_Pass_HPP
#define __WHISKEY_AST_Pass_HPP

#include <string>
#include <vector>

#include <whiskey/AST/PassResult.hpp>

namespace whiskey {
class Node;
class MessageContext;

class Pass {
private:
  std::string name;
  std::vector<std::string> dependencies;

protected:
  virtual PassResult onRunPre(Node &node, MessageContext &msgs) = 0;
  virtual PassResult onRunPost(Node &node, MessageContext &msgs) = 0;

public:
  Pass(std::string name, std::initializer_list<std::string> dependencies = {});
  Pass(const Pass &) = delete;
  virtual ~Pass();

  const std::string &getName() const;
  const std::vector<std::string> &getDependencies() const;

  PassResult runPre(Node &node, MessageContext &msgs);
  PassResult runPost(Node &node, MessageContext &msgs);
};
} // namespace whiskey

#endif
