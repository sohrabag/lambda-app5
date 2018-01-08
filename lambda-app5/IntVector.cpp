#include "stdafx.h"
#include "IntVector.h"




IntVector::IntVector()
{
}


IntVector::~IntVector()
{
}

Iter2 IntVector::begin() const
{
	return Iter2(0, this);
}

Iter2 IntVector::end() const
{
	return Iter2(100, this);
}

int IntVector::get(int pos) const
{

	return _data[pos];
}

void
IntVector::set(int pos, int val)
{
	_data[pos] = val;
}

int
Iter2::operator*()
{
	return _IntVec->get(_pos);
}