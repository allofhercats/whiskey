#ifndef __WHISKEY_Passes_Pass_HPP
#define __WHISKEY_Passes_Pass_HPP

#include <string>
#include <vector>

namespace whiskey {
class Node;

class Pass {
private:
  std::string name;
  std::vector<std::string> dependencies;

protected:
  virtual Node *onRunPre(Node *node) = 0;
  virtual Node *onRunPost(Node *node) = 0;

public:
  Pass(std::string name, std::initializer_list<std::string> dependencies = {});
  Pass(const Pass &) = delete;
  virtual ~Pass();

  const std::string &getName() const;
  const std::vector<std::string> &getDependencies() const;

  Node *runPre(Node *node);
  Node *runPost(Node *node);
};
} // namespace whiskey

#endif
