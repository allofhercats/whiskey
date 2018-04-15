#ifndef __WHISKEY_CodeGen_Generator_HPP
#define __WHISKEY_CodeGen_Generator_HPP

namespace whiskey {
class Node;

class Generator {
protected:
	virtual void onGenerateUnit(const Node &node) = 0;

public:
	Generator();
	Generator(const Generator &) = delete;
	virtual ~Generator();

	void generateUnit(const Node &node);
};
}

#endif
