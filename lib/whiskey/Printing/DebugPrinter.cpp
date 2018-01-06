#include <whiskey/Printing/DebugPrinter.hpp>

#include <whiskey/Core/Color.hpp>

namespace whiskey {
void DebugPrinter::onPrint(std::ostream &os,
                           const Node *node,
                           unsigned int indent) {
  if (node == nullptr) {
    os << "null";
    return;
  }

  os << Color::greenLight << Node::getKindInfo(node->getKind()).getName()
     << Color::reset;
  for (int i = 0; i < Node::getKindInfo(node->getKind()).getNFields(); i++) {
    const Field *field = node->getField(i);
    W_ASSERT_NONNULL(field, "Cannot print null field.");

    Node::FieldTagInfo fit = Node::getFieldTagInfo(
        Node::getKindInfo(node->getKind()).getFieldTag(i));

    if (field->getKind() == Field::Kind::Node) {
      if (fit.isExpectingList()) {
        int n = 0;
        for (const Node *i = field->getNode(); i != nullptr; i = i->getNext()) {
          W_ASSERT_NONNULL(i, "Cannot print null node as list element.");

          printNewline(os, indent + 1);

          os << Color::cyan << fit.getName() << "[" << n << "] "
             << Color::reset;
          print(os, i, indent + 1);
          n++;
        }
      } else {
        printNewline(os, indent + 1);
        os << Color::cyan << fit.getName() << ":" << Color::reset;
        print(os, field->getNode(), indent + 1);
      }
    } else {
      printNewline(os, indent + 1);
      os << Color::cyan << fit.getName() << ":" << Color::yellowLight;
      field->printLiteral(os);
      os << Color::reset;
    }
  }
}

DebugPrinter::DebugPrinter(unsigned int tabWidth) : Printer(false, tabWidth) {
}
} // namespace whiskey
