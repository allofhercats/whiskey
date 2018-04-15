#ifndef __WHISKEY_Parsing_ParserResult_HPP
#define __WHISKEY_Parsing_ParserResult_HPP

#include <whiskey/AST/Node.hpp>

namespace whiskey {
class ParserResult {
private:
  std::unique_ptr<Node> node;
  bool good;

public:
  ParserResult();
  ParserResult(const std::unique_ptr<Node> &node);

  std::unique_ptr<Node> &getNode();
  const std::unique_ptr<Node> &getNode() const;
  void setNode(std::unique_ptr<Node> value);

  bool isGood() const;
  void setGood(bool value);
};
} // namespace whiskey

#endif
