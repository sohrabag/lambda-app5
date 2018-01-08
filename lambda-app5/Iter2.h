#pragma once


class IntVector;

class Iter2
{
public:
	Iter2(int pos, const IntVector * inVec)	: _pos(pos), 
		_IntVec(inVec)
	{
	}
	Iter2();
	~Iter2();

	//methods and overloads
	bool operator!=(const Iter2& other)
	{
		return _pos != other._pos;
	}

	bool operator==(const Iter2& other)
	{
		return _pos == other._pos;
	}

	Iter2& operator=( Iter2& other)
	{
		return other;
	}

	const Iter2& operator++()
	{
		_pos++;
		return *this;
	}
	int operator*();


private:
	int _pos;
	const IntVector * _IntVec;
};

