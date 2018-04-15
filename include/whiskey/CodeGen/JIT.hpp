#ifndef __WHISKEY_CodeGen_JIT_HPP
#define __WHISKEY_CodeGen_JIT_HPP

#include <string>
#include <functional>

namespace whiskey {
class JIT {
protected:
	virtual void *onCompile(const std::string &name) = 0;

public:
	JIT();
	JIT(const JIT &) = delete;
	virtual ~JIT();

	template<typename T>
	std::function<T> compile(const std::string &name);
};
}

#include <whiskey/CodeGen/JIT.tpp>

#endif
