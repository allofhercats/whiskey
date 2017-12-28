#ifndef __WHISKEY_AST_StmtBlock_HPP
#define __WHISKEY_AST_StmtBlock_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtBlock : public Stmt {
private:
  std::vector<Container<Stmt>> body;

protected:
  virtual AST *onClone() const;

  bool onCompareStmt(const Stmt &other) const;
  void onGetChildrenStmt(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareStmtBlock(const StmtBlock &other) const;
  virtual void onGetChildrenStmtBlock(std::queue<ContainerRef<AST>> &children);

public:
  StmtBlock(std::vector<Container<Stmt>> body = {});
  StmtBlock(Range range, std::vector<Container<Stmt>> body = {});

  std::vector<Container<Stmt>> &getBody();
  const std::vector<Container<Stmt>> &getBody() const;
};
} // namespace whiskey

#endif
