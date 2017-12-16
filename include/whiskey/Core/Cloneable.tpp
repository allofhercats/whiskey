namespace whiskey {
template<class SelfType>
Cloneable<SelfType>::Cloneable()
{}

template<class SelfType>
Cloneable<SelfType>::~Cloneable()
{}

template<class SelfType>
SelfType *Cloneable<SelfType>::clone() const
{
	return onClone();
}

template<class SelfType>
template<class ResType>
ResType *Cloneable<SelfType>::cloneAs() const
{
	return static_cast<ResType *>(clone());
}
}
