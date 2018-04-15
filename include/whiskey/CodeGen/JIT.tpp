namespace whiskey {
template<typename T>
std::function<T> JIT::compile(const std::string &name) {
	return reinterpret_cast<T *>(onCompile(name));
}
}
