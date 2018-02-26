namespace whiskey {
template<class T>
T &Field::as() {
	return static_cast<T &>(*this);
}

template<class T>
const T &Field::as() const {
	return static_cast<const T &>(*this);
}
}