namespace whiskey {
template<class ValueType>
Ref<ValueType>::Ref(ValueType *value) : value(value) {}

template<class ValueType>
Ref<ValueType>::operator bool() const {
	return value != nullptr;
}

template<class ValueType>
Ref<ValueType>::operator CRef<ValueType>() const {
	return CRef<ValueType>(value);
}

template<class ValueType>
ValueType *Ref<ValueType>::operator->() {
	W_ASSERT_NONNULL(value, "Cannot access null value.");
	return value;
}

template<class ValueType>
const ValueType *Ref<ValueType>::operator->() const {
	W_ASSERT_NONNULL(value, "Cannot access null value.");
	return value;
}

template<class ValueType>
ValueType &Ref<ValueType>::operator*() {
	W_ASSERT_NONNULL(value, "Cannot access null value.");
	return *value;
}

template<class ValueType>
const ValueType &Ref<ValueType>::operator*() const {
	W_ASSERT_NONNULL(value, "Cannot access null value.");
	return *value;
}
}
