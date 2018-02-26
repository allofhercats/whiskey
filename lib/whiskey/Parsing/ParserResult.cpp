#include <whiskey/Parsing/ParserResult.hpp>

namespace whiskey {
ParserResult::ParserResult() : good(false) {
}

ParserResult::ParserResult(Node node) : node(node), good(true) {
}

Node &ParserResult::getNode() {
  return node;
}

const Node &ParserResult::getNode() const {
  return node;
}

void ParserResult::setNode(Node value) {
  node = value;
}

bool ParserResult::isGood() const {
  return good;
}

void ParserResult::setGood(bool value) {
  good = value;
}
} // namespace whiskey
