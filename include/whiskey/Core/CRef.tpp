namespace whiskey {
template<class ValueType>
CRef<ValueType>::CRef(const ValueType *value) : value(value) {}

template<class ValueType>
CRef<ValueType>::operator bool() const {
	return value != nullptr;
}

template<class ValueType>
const ValueType *CRef<ValueType>::operator->() const {
	W_ASSERT_NONNULL(value, "Cannot access null value.");
	return value;
}

template<class ValueType>
const ValueType &CRef<ValueType>::operator*() const {
	W_ASSERT_NONNULL(value, "Cannot access null value.");
	return *value;
}
}
