namespace whiskey {
template<class ValueType>
ContainerRef<ValueType>::ContainerRef() : value(nullptr) {}

template<class ValueType>
template<class ContainerType>
ContainerRef<ValueType>::ContainerRef(Container<ContainerType> &value) : value((ValueType **)(&value.value)) {}

template<class ValueType>
ContainerRef<ValueType>::operator bool() const {
	return value != nullptr && *value;
}

template<class ValueType>
ContainerRef<ValueType>::operator Container<ValueType>() {
	return *value;
}

template<class ValueType>
ContainerRef<ValueType>::operator Ref<ValueType>() {
	return *value;
}

template<class ValueType>
ContainerRef<ValueType>::operator CRef<ValueType>() const {
	return *value;
}

template<class ValueType>
ValueType *ContainerRef<ValueType>::operator->() {
	return &(**value);
}

template<class ValueType>
const ValueType *ContainerRef<ValueType>::operator->() const {
	return &(**value);
}

template<class ValueType>
ValueType &ContainerRef<ValueType>::operator*() {
	return **value;
}

template<class ValueType>
const ValueType &ContainerRef<ValueType>::operator*() const {
	return **value;
}

template<class ValueType>
void ContainerRef<ValueType>::replace(ValueType *value) {
	delete *this->value;
	*this->value = value;
}
}
