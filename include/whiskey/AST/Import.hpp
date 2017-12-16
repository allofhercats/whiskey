#ifndef __WHISKEY_AST_Import_HPP
#define __WHISKEY_AST_Import_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Import : public AST {
private:
	std::string path;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareImport(const Import &other) const;

public:
	Import(std::string path);
	Import(Range range, std::string path);

	const std::string &getPath() const;
	void setPath(std::string value);
};
}

#endif
