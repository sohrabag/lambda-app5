#pragma once

#include <utility>
/*
In this class we n
Movable class: two components are needed to be developed
1. Movable constructor 
2. Movable Assignment operator
*/
class Movable
{
public:
	//use explicit when you have only one argument in the constructor/or one argument for all other 
	//parameters default preset to some value
	explicit Movable(size_t size=512)	: _pBuf(new char[size]), _size(size){}
	explicit Movable(const char * p, size_t size = 512) : _size(size){
		assert(p);
		_pBuf = new char[_size];
		assert(_pBuf);
		for (unsigned i = 0; i < _size; i++) { _pBuf[i] = p[i]; }
	}

	//non-move copy constructor
	Movable(const Movable& other) : _size(other._size), _pBuf(new char[other._size])
	{
		::memset((void*)_pBuf, 0, _size);
	}

	Movable& operator=(const Movable& rhs) {
		if (this != &rhs) { delete[] _pBuf; _size = rhs._size; _pBuf = new char[_size]; 
		for (unsigned i = 0; i < _size; i++)  _pBuf[i] = rhs._pBuf[i];
		}

		return *this;
	}

	//move copy constructor
	Movable( Movable&& other)	: _size(other._size),_pBuf(new char[other._size])
	{
		//pilfiller other's resources
		_pBuf = other._pBuf;
		_size = other._size;
		//reset the other
		other._pBuf = nullptr;
		other._size = 0;
	}

	Movable&& operator=(Movable&& other)
	{
		_pBuf = other._pBuf;
		_size = other._size;
		//
		_size = 0;
		_pBuf = nullptr;
	}

	virtual ~Movable()
	{
		delete[] _pBuf;
	}

	//public methods
	friend ostream& operator << (ostream& out, const Movable& rhs) {
		out << rhs._pBuf << endl;

		return out;
	}

private:
	char * _pBuf;
	size_t	_size;
};

