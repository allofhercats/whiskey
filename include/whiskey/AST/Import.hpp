#ifndef __WHISKEY_AST_Import_HPP
#define __WHISKEY_AST_Import_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Import : public AST {
private:
  std::string path;

protected:
  virtual AST *onClone() const;

  bool onCompare(const AST &other) const;
  void onGetChildren(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareImport(const Import &other) const;
  virtual void onGetChildrenImport(std::queue<ContainerRef<AST>> &children);

public:
  Import(std::string path);
  Import(Range range, std::string path);

  const std::string &getPath() const;
  void setPath(std::string value);
};
} // namespace whiskey

#endif
