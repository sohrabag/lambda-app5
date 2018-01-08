#pragma once

#include <iostream>
//class A is a friend with class FriendClass
class FriendClass
{
public:
	FriendClass();
	~FriendClass();
	FriendClass(int a, int b) : _x(a), _y(b){}
	//copy constructor
	FriendClass(const FriendClass& obj)
	{
		_x = obj._x; _y = obj._y;
	}

	friend class A;

private:
	int _x;
	int _y;
};

class A 
{
public:
	A(){}
	~A(){}
	friend class FriendClass;

	//methods
	void AccessFriendClass(FriendClass a) {
		std::cout << a._x << " " << a._y << std::endl;
	}
};
