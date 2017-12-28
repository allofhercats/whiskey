#ifndef __WHISKEY_AST_DeclNamespace_HPP
#define __WHISKEY_AST_DeclNamespace_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Decl.hpp>
#include <whiskey/AST/Type.hpp>

namespace whiskey {
class DeclNamespace : public Decl {
private:
  std::vector<Container<Decl>> members;

protected:
  virtual AST *onClone() const;

  bool onCompareDecl(const Decl &other) const;
  void onGetChildrenDecl(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareDeclNamespace(const DeclNamespace &other) const;
  virtual void
  onGetChildrenDeclNamespace(std::queue<ContainerRef<AST>> &children);

public:
  DeclNamespace(std::string name, std::vector<Container<Decl>> members = {});
  DeclNamespace(Range range,
                std::string name,
                std::vector<Container<Decl>> members = {});

  std::vector<Container<Decl>> &getMembers();
  const std::vector<Container<Decl>> &getMembers() const;
};
} // namespace whiskey

#endif
