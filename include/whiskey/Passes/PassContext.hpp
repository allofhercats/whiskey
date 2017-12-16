#ifndef __WHISKEY_Passes_PassContext_HPP
#define __WHISKEY_Passes_PassContext_HPP

#include <whiskey/Passes/Module.inc>

namespace whiskey {
template<class T>
class PassContext {
public:
	enum Status {
		Continue,
		BreakFromBranch,
		BreakFromTree
	};

private:
	CRef<AST> parent;
	Ref<T> original;
	Container<AST> replacement;
	Status status;

public:
	PassContext(CRef<AST> parent, Ref<T> original);

	template<class U>
	PassContext<U> as();

	Ref<T> getOriginal();
	CRef<AST> getParent();
	Container<AST> &getReplacement();
	void setReplacement(Container<AST> value);

	Status getStatus() const;
	void setStatus(Status value);
};
}

#include <whiskey/Passes/PassContext.tpp>

#endif
