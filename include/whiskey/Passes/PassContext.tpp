namespace whiskey {
template<class T>
PassContext<T>::PassContext() {}

template<class T>
PassContext<T>::PassContext(CRef<AST> parent, Ref<T> original) : parent(parent), original(original) {}

template<class T>
template<class U>
PassContext<U> PassContext<T>::branch() {
	return PassContext<U>(parent, original->template as<U>());
}

template<class T>
template<class U>
void PassContext<T>::merge(PassContext<U> &other) {
	replacement = other.getReplacement();

	other.setReplacement(nullptr);
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
}
