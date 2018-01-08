// lambda-app2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "Iter2.h"
#include "IntVector.h"
#include "AddressBook.h"
#include "FriendClass.h"
#include "complex.h"

#include "HeapTree.h"

using namespace std;

//============================
class foo {
public:
	foo() : _x(3) { _vec.push_back("item1"); _vec.push_back("item2"); }
	void func() {
		//pure lambda expression is used in this part and we need to do that 
		[this]() -> int { cout << _x; cout << endl << "the all are in one line" << endl; return _x; } ();
		//for each go through collection vector without using lambda 
		for each (auto item in _vec)
		{
			cout << item.c_str() << endl;
		}
		//regular for loop without any lambda
		for (auto iter = _vec.begin(), end = _vec.end(); iter != end; iter++)
		{
			cout << iter->c_str() << endl;
		}
		//function from STL algorithms
		for_each(_vec.begin(), _vec.end(), [](string val) {cout << val.c_str() << endl; });
	}

	void print()
	{
		[this]() {auto iter = _vec.cbegin();  do { cout << iter->c_str() << endl; } while (++iter != _vec.cend()); this->printsomething(); }();
	}
	void printsomething() { cout << "The this pointer is captured in lambda expression" << endl; }
private:
	int _x;
	vector<string> _vec;
};


//with this class we register a handler function , which is a call back function 
class EmailProcessor
{
public:
	EmailProcessor() {}

	void ReceiveMessage(const string& message)
	{
		if (_handler_func)
		{
			_handler_func(message);
		}
	}
	void SetHandlerFunc(function<void(const string&)> handler_func)
	{
		_handler_func = handler_func;
	}

private:
	function<void(const string&)> _handler_func;
};


//this class stores the received message with max size
class MsgSizeStore {
private:
	int _maxSize;
public:
	//constructor
	MsgSizeStore() : _maxSize(0) {}

	void checkMessage(const string& msg) {
		if (msg.size() > (unsigned)_maxSize)
			_maxSize = msg.size();
	}
};


int main()
{

#if 0
	//lambda expressions
	[]() {}; //simplest form
			 //declare foo class
	foo fuu;
	//call func method
	fuu.func();
	//	_________________________________
	typedef int(*f)(int);
	int name = 90;
	f f1 = [](int i) -> int { cout << "The value of i is:" << i << endl; return i; };
	int j = f1(10);
	//_______________________________________________________

	//using class AddressBook
	AddressBook addresses;
	vector<string> result = addresses.FindAddress(
		[](const string& address) {
		return address.find(".org") != string::npos;
	}
	);

	vector<string> result1 = addresses.FindAddress(
		[](const string& address) {
		return address.find(".net") != string::npos;
	}
	);
	//some nested lambda code for printing a thing
	[&]() {for_each(result.begin(), result.end(), [](string val) {cout << val << endl; }); } ();

	//print list of address with .net post fix
	[&]() {for (auto iter = result1.cbegin(); iter != result1.cend(); iter++) cout << iter->c_str() << endl; }();
	//print with new lambda-enabled print methos in foo class
	fuu.print();

	//FindAddress2 method uses FindAddress2 method
	vector<string> result3 = addresses.FindAddress2(
		[](const string& address) {return address.find(".net") != string::npos; }
	);
	[]() {cout << "This the result of the std::function<bool (const string& )> template  passed as function to findaddress2 method and lambda passed as parameter for std::function template." << endl; }();
	[&]() {for_each(result3.cbegin(), result3.cend(), [](string val) {cout << val.c_str() << endl; }); }();

	//create a delegate with help of lambda expression
	//During 
	EmailProcessor EMP;
	MsgSizeStore MSS;
	EMP.SetHandlerFunc(
		[&](const string& msg) {MSS.checkMessage(msg); }
	);

	//Iter and IntVector classes testing
	IntVector col;

	for (int i = 0; i < 100; i++)
	{
		col.set(i, i);
	}

	//this is how in C++11 range-based collection is printed, Iter2 is written so that it supports the printing 
	//of a ranged-based lists.
	for (int i : col)
		cout << col.get(i) << " ";
	cout << endl;

	for (Iter2 it = col.begin(); it != col.end(); ++it) //attention: operator++ is a prefix operator so ++it must be used.
		cout << *it << " ";
	cout << endl;

	//conpy constructor
	FriendClass friend1(1, 2);
	FriendClass friend2;
	friend2 = friend1;		//copy constructor is called here.
	A a;// class A is a friend class to FriendClass
	a.AccessFriendClass(friend2);

	//complex numbers operations
	complex a1, b(10.0,10.0);
	a1 = b;
	complex c = a1 + b;
	c.print();

	cout << c;

#endif
	
	HeapTree<int> hp;
	//enter sohrab into the heap
	hp.Insert('S');	hp.Insert('O');
	hp.Insert('H');	hp.Insert('R');
	hp.Insert('A');	hp.Insert('B');
	cout << hp;

	return 0;
}
