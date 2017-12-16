namespace whiskey {
template<class T>
PassContext<T>::PassContext(CRef<AST> parent, Ref<T> original) : parent(parent), original(original), status(PassContext<T>::Continue) {}

template<class T>
template<class U>
PassContext<U> PassContext<T>::as() {
	return PassContext<U>(parent, original->template as<U>());
}

template<class T>
Ref<T> PassContext<T>::getOriginal() {
	return original;
}

template<class T>
CRef<AST> PassContext<T>::getParent() {
	return parent;
}

template<class T>
Container<AST> &PassContext<T>::getReplacement() {
	return replacement;
}

template<class T>
void PassContext<T>::setReplacement(Container<AST> value) {
	replacement = value;
}

template<class T>
typename PassContext<T>::Status PassContext<T>::getStatus() const {
	return status;
}

template<class T>
void PassContext<T>::setStatus(PassContext<T>::Status value) {
	status = value;
}
}
