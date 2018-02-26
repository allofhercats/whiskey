namespace whiskey {
template<class T>
T &ParserRule::as() {
	return static_cast<T &>(*this);
}

template<class T>
const T &ParserRule::as() const {
	return static_cast<const T &>(*this);
}
}