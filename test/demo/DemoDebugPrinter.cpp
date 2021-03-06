#include <iostream>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/Printing/DebugPrinter.hpp>

using namespace whiskey;

int main() {
  DebugPrinter dp;

  dp.print(std::cout, Node::createTypeAtomicBool());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicInt8());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicInt16());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicInt32());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicInt64());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicUInt8());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicUInt16());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicUInt32());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicUInt64());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicFloat32());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicFloat64());
  std::cout << "\n\n";

  dp.print(std::cout, Node::createTypeAtomicReal());
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createTypeSymbol(Field::createString(new StringContainer("x")),
                                  {Node::createTypeAtomicInt32()}));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createTypeSymbol(Field::createString(new StringContainer("x")),
                                  {Node::createTypeAtomicInt32(),
                                   Node::createExprSymbol(Field::createString(
                                       new StringContainer("x")))}));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createTypeAccessUnary(Node::createTypeSymbol(
               Field::createString(new StringContainer("x")))));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createTypeFunction(
               Node::createTypeAtomicInt32(),
               {Node::createTypeAtomicInt32(), Node::createTypeAtomicInt32()}));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createExprLiteralUInt(Node::createTypeAtomicUInt64(), 5));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createExprLiteralReal(Node::createTypeAtomicFloat64(), 3.14));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createExprSymbol(Field::createString(new StringContainer("x")),
                                  {Node::createTypeAtomicInt32(),
                                   Node::createExprSymbol(Field::createString(
                                       new StringContainer("x")))}));
  std::cout << "\n\n";

  dp.print(
      std::cout,
      Node::createExprCall(
          Node::createExprSymbol(Field::createString(new StringContainer("f"))),
          {Node::createExprSymbol(
               Field::createString(new StringContainer("x"))),
           Node::createExprSymbol(
               Field::createString(new StringContainer("y")))}));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createExprBoolNot(Node::createExprSymbol(
               Field::createString(new StringContainer("x")))));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createExprBoolAnd({Node::createExprSymbol(Field::createString(
                                        new StringContainer("x"))),
                                    Node::createExprSymbol(Field::createString(
                                        new StringContainer("y")))}));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createExprGroup(Node::createExprSymbol(
               Field::createString(new StringContainer("x")))));
  std::cout << "\n\n";

  dp.print(std::cout, Node::createStmtEmpty());
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtExpr(Node::createExprSymbol(
               Field::createString(new StringContainer("x")))));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtReturn(Node::createExprSymbol(
               Field::createString(new StringContainer("x")))));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtIf(Node::createExprSymbol(Field::createString(
                                  new StringContainer("x"))),
                              Node::createStmtEmpty()));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtIf(Node::createExprSymbol(Field::createString(
                                  new StringContainer("x"))),
                              Node::createStmtEmpty(),
                              Node::createStmtEmpty()));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtWhile(Node::createExprSymbol(
               Field::createString(new StringContainer("x")))));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtWhile(Node::createExprSymbol(Field::createString(
                                     new StringContainer("x"))),
                                 Node::createStmtEmpty()));
  std::cout << "\n\n";

  dp.print(std::cout, Node::createStmtFor({}, nullptr, {}));
  std::cout << "\n\n";

  dp.print(
      std::cout,
      Node::createStmtFor(
          {Node::createDeclVariable(
               Node::createTypeAtomicInt32(),
               Field::createString(new StringContainer("x"))),
           Node::createDeclVariable(
               Node::createTypeAtomicInt32(),
               Field::createString(new StringContainer("y")))},
          Node::createExprSymbol(Field::createString(new StringContainer("x"))),
          {Node::createExprSymbol(
               Field::createString(new StringContainer("x"))),
           Node::createExprSymbol(
               Field::createString(new StringContainer("y")))},
          Node::createStmtEmpty()));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtForEach(
               {Node::createDeclVariable(
                   Node::createTypeAtomicInt32(),
                   Field::createString(new StringContainer("x")))},
               {Node::createExprSymbol(
                   Field::createString(new StringContainer("y")))}));
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtForEach(
               {Node::createDeclVariable(
                   Node::createTypeAtomicInt32(),
                   Field::createString(new StringContainer("x")))},
               {Node::createExprSymbol(
                   Field::createString(new StringContainer("y")))},
               Node::createStmtEmpty()));
  std::cout << "\n\n";

  dp.print(std::cout, Node::createStmtBlock());
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createStmtBlock(
               {Node::createStmtEmpty(), Node::createStmtEmpty()}));
  std::cout << "\n\n";

  dp.print(
      std::cout,
      Node::createDeclVariable(Node::createTypeAtomicInt32(),
                               Field::createString(new StringContainer("x"))));
  std::cout << "\n\n";

  Node *dv0 = Node::createDeclVariable(
      Node::createTypeAtomicInt32(),
      Field::createString(new StringContainer("x")),
      {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("z"))),
       Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("w")))},
      Node::createExprSymbol(Field::createString(new StringContainer("y"))));
  dp.print(std::cout, dv0);
  std::cout << "\n\n";

  dp.print(
      std::cout,
      Node::createDeclFunction(Node::createTypeAtomicInt32(),
                               Field::createString(new StringContainer("f")),
                               {}));
  std::cout << "\n\n";

  Node *df0 = Node::createDeclFunction(
      Node::createTypeAtomicInt32(),
      Field::createString(new StringContainer("f")),
      {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("z"))),
       Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("w")))},
      {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("x"))),
       Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("y")))},
      Node::createStmtEmpty());
  dp.print(std::cout, df0);
  std::cout << "\n\n";

  dp.print(
      std::cout,
      Node::createDeclClass(Field::createString(new StringContainer("a"))));
  std::cout << "\n\n";

  Node *dc0 = Node::createDeclClass(
      Field::createString(new StringContainer("a")),
      {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("z"))),
       Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("w")))},
      {Node::createTypeAtomicInt32(), Node::createTypeAtomicInt64()},
      {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("x"))),
       Node::createDeclVariable(
           Node::createTypeAtomicInt32(),
           Field::createString(new StringContainer("y")))});
  dp.print(std::cout, dc0);
  std::cout << "\n\n";

  dp.print(
      std::cout,
      Node::createDeclNamespace(Field::createString(new StringContainer("a"))));
  std::cout << "\n\n";

  Node *dn0 = Node::createDeclNamespace(
      Field::createString(new StringContainer("a")),
      {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                Field::createString(new StringContainer("x"))),
       Node::createDeclVariable(
           Node::createTypeAtomicInt32(),
           Field::createString(new StringContainer("y")))});
  dp.print(std::cout, dn0);
  std::cout << "\n\n";

  dp.print(std::cout,
           Node::createImport(Field::createString(new StringContainer("M"))));
  std::cout << "\n\n";

  dp.print(
      std::cout,
      Node::createUnit({Node::createDeclVariable(
                            Node::createTypeAtomicInt32(),
                            Field::createString(new StringContainer("x"))),
                        Node::createDeclVariable(
                            Node::createTypeAtomicInt32(),
                            Field::createString(new StringContainer("y")))}));
  std::cout << "\n\n";

  return 0;
}
