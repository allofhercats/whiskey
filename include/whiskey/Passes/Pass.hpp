#ifndef __WHISKEY_Passes_Pass_HPP
#define __WHISKEY_Passes_Pass_HPP

#include <string>
#include <vector>

namespace whiskey {
class Node;
class MessageContext;

class Pass {
private:
  std::string name;
  std::vector<std::string> dependencies;

protected:
  virtual bool onRunPre(Node &node, MessageContext &msgs) = 0;
  virtual bool onRunPost(Node &node, MessageContext &msgs) = 0;

public:
  Pass(std::string name, std::initializer_list<std::string> dependencies = {});
  Pass(const Pass &) = delete;
  virtual ~Pass();

  const std::string &getName() const;
  const std::vector<std::string> &getDependencies() const;

  bool runPre(Node &node, MessageContext &msgs);
  bool runPost(Node &node, MessageContext &msgs);
};
} // namespace whiskey

#endif
