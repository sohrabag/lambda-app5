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
#include "Queue.h"

#include <sstream>
#include <fstream>


//matlab include files
#include <C:\Program Files\MATLAB\R2015b\extern\include\engine.h>
#include <C:\Program Files\MATLAB\R2015b\extern\include\mat.h>
#include <C:\Program Files\MATLAB\R2015b\extern\include\matrix.h>
#include <C:\Program Files\MATLAB\R2015b\extern\include\mex.h>

#pragma comment(lib, "libmat.lib")
#pragma comment (lib, "libeng.lib")
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libmex.lib")

//Matrix operations 1D
#include "Mat_Lib.h"

//multi-threading headers
#include <thread>
#include <atomic>
#include <mutex>

//user created worker thread.
#include "do_work.h"

using namespace std;
using namespace Mysapce;

/*===========================================================*/
/* multi-threadin related code snippet worker function */
#include <string>
/*=============================================================*/
void dosomething() {
	cout << "A worker thread is called here ." << endl;
}

atomic<bool> ready(false);
std::atomic<bool> winner(false);
mutex m;


void count1m(int th_id) {
	while(!ready){}
	unique_lock<mutex> lk(m);
	for (int i = 0; i < 1000000; i++) {}
	if (!winner.exchange(true)) { cout << "thread #: " << th_id << "counted 1 million ." << endl; }
//	this_thread::sleep_for(chrono::milliseconds(10));
	cout << "thread #: " << th_id << "counted 1 million ." << endl;
}

/*======================== POSIX thread or pthread in c ========================*/
//#include <pthread.h>
/*=============================================================================*/
//lvalue och rvalue concepts lvalue only (&) and rvalue (&&) and this is the basic behind this
//rvalue has no name on the contrary lvalue has name
//int a, b; a * b; multiplication expresion has no name so it is a rvalue. but a and b individally
//are lvalues!

//header of class Movable
#include "Movable.h"

//rvalue reference
int x = 10;
int foo1() { return x; }
int& bar() { return x; }
int&& baz() { return 10; }
//=========================================================================
//shared_ptr   and unique_ptr concepts. each time something assigns to a pointer
//its count_use is increased.
#include <memory>
#include <algorithm>
void myfunc(unique_ptr<int> p) {cout << *p; }

void disp(vector<int> v, ostream& os) {
	for_each(v.begin(), v.end(), [&os](int i) { os << i << " "; });
}

/* 
constant object with mutable data members that can be modified
*/

#include "Mutable.h"
#include <ctime>

constexpr std::size_t Countlower(conststr s, std::size_t n = 0,
	std::size_t c = 0) {
	return n == s.Size() ? c : 'a' <= s[n] && s[n] <= 'z' ? Countlower(s, n+1,c+1) :
		Countlower(s, n+1,c);
}

template<int n>
struct CONSTN {
	CONSTN() {
		std::cout << n << endl;
	}
};

constexpr int f();				//constexpr function f() is only declared
constexpr int f() { return 2; } //constexpr function is defined as well 
								//so it is no problem to use in main program
/*---------------------------------------------------------*/
#include <bitset>
/*----------------------------------------------------------*/

/*====================    static_assert, is_trivial_constructable<T>::value     ===========================*/

#include <type_traits>

struct X {
	X() = default;
};

struct Y {
	Y(){}
};
/*------------------------------------------------*/
struct EX1 {
	std::string str;	//the copy constructor is not trivial
};

struct EX2 {//copy
	int n;
	EX2(const EX2&) = default;	//trivial and non-throwing
};

/*---------------------------------------------------*/
/*============ Type Conversions static_cast, dynamic_cast, reinterpret_cast , and etc. ===============*/
#include "TypeConv.h"

/*========================== sorting algorithms and comparison of their performances ===================*/
#include "SortLib.h"

/*======================= Graph processing headers==========================*/
#include "Graph.h"

//==========================================================================
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
			_maxSize = (unsigned)msg.size();
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
	complex a1, b(10.0, 10.0);
	a1 = b;
	complex c = a1 + b;
	c.print();

	cout << c;



	HeapTree<char> hp;
	//enter sohrab into the heap
	hp.Insert('S');
	cout << hp;
	hp.Insert('O');
	cout << hp;
	hp.Insert('H');
	cout << hp;
	hp.Insert('R');
	cout << hp;
	hp.Insert('A');	
	cout << hp;
	hp.Insert('B');
	cout << hp;
	hp.RemoveTree();

	HeapTree<int> hp1;
	hp1.Insert(1);
	cout << hp1;
	hp1.Insert(3);
	cout << hp1;
	hp1.Insert(2);
	cout << hp1;
	hp1.Insert(4);
	cout << hp1;
	hp1.Insert(5);	

	cout << hp1;
	hp1.RemoveTree();

	//Queue some items by the way we could use a loop here easily not a good practice just for testing reasons!
	Queue<int> Q(10);
	Q.Enqueue(0);
	cout << Q << endl;
	Q.Enqueue(1);
	cout << Q << endl;
	Q.Enqueue(2);
	cout << Q << endl;
	Q.Enqueue(3);
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.Enqueue(4);
	cout << Q << endl;
	Q.Enqueue(5);
	cout << Q << endl;
	Q.Enqueue(6);
	cout << Q << endl;
	Q.Enqueue(7);
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.Enqueue(8);
	cout << Q << endl;
	cout << "Size of the Queue is: " << Q.Size() << endl;
	Q.Enqueue(9);
	cout << Q << endl;
	Q.Enqueue(10);
	cout << Q << endl;
	Q.Enqueue(11);
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;

	cout << "Size of the Queue is: " << Q.Size() << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;
	Q.dequeue();
	cout << Q << endl;


	//hash tables, keyed arrays vs indexed arrays, collision in hash table, O(1) is the performance.


	//IO streams and their applications
	int x;
	cout << "please enter an integer value" << endl;
	if (cin >> x) {
		cout << "value of x is: " << x << endl;
	}


	{
		//important note**: at least one character must be after the number otherwise this program wont work.
		//"Here is a double number : 74.44." or "Here is a double number : 74.44. "
		string dat("Here is a double number : 74.44.");
		stringstream mystream(ios::in | ios::out);
		mystream.str(dat);
		mystream.seekg(-6, ios::end);
		double num;
		mystream >> num;
		double val = num * num;
		mystream.seekp(-6, ios::end);
		mystream << val;
		string newval = mystream.str();
		cout << newval << endl;
	}
		//shorter version of the previous program.
	{
		stringstream star(ios::in | ios::out);
		star.str("This is another double number: 55.34.  ");
		star.seekg(-8, ios::end);
		cout << "The position of the get pointer : " << star.tellg() << endl;
		double val;
		star >> val;
		val *= val;
		star.seekp(-8, ios::end);
		cout << "The position of the the put pointer : " << star.tellp() << endl;
		star << val;
		cout << star.str() << endl;
	}

	{
		//file stream operations
		ofstream ofs(".\\stream.txt", ios::app);
		if (ofs.good()) {
			ofs << "this is some text for you stream.txt file put it at the end of your file.";
			ofs << "This is another piece of text that i add to the end of the file again.";
		}
	}

	//read a file into the stream

	//lower level operations
	ifstream ifs("stream.txt", ios::binary);
	auto const start_pos = ifs.tellg();
	ifs.ignore(numeric_limits<streamsize>::max());
	auto count = ifs.gcount();
	ifs.seekg(start_pos);
	auto s = string(count, char{});
	cout << s.size() << endl;
	ifs.read(&s[0], s.size());
	ofstream ofs("stream1.txt", ios::trunc);
	if (ofs.good())
		ofs << s.c_str();

	{
		//Matrix operations 1D
		Mat_Lib_1D<int> a(HORIZONTAL, STANDARD);
		Mat_Lib_1D<int> b(VERTICAL, STANDARD);
		Mat_Lib_1D<int> c(NONE, NONE);

		cout << "Enter values for a STANDARD size Matrix." << endl;
		cin >> a;
		//skip few line 
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		Mat_Lib_1D<int> d(HORIZONTAL, STANDARD);
		d = a;
		d = d + a;
		cout << a;
		cout << endl; cout << endl;
		cout << d << endl;

		cout << "Multiplication operation : d * a" << endl;
		d = d * a;
		cout << d << endl;

		cout << "Division Operation : d / a" << endl;
		d = d / a;
		cout << d << endl;

	}


	{

		//enumVector template simulates a enum template
		//I DONT SEE MUCH OF USE FOR THIS TEMPLATE THOUGH!
		enumVector<Mat_Type, int> ent(LARGE);
		ent[NONE] = 10;

		//Name_list is an enum type in the Mat_Lib.h header file!!!!
		enumVector<Name_list, int> ent_str(rahi);
		ent_str[sohrab] = 1237;
		ent_str[arezou] = 1506;
		ent_str[mahlagha] = 2000;
		ent_str[rahi] = 1903;

		cout << ent_str[arezou] << endl;
	}



	{
		Mat_Lib_2D<double>  mat1(2,2,0.1);	//a 2x2 2D matrix with its elements initialized to .1
		Mat_Lib_2D<double>  mat2(2, 2, 0.1);//a 2x2 2D matrix with its elements initialized to .1

		//ask the user to enter values for elements of the matrix
		cout << "Please enter the values for the matrix: " << endl;
		cin >> mat1;
		cout << mat1;

		cout << "Please enter the values for the matrix: " << endl;
		cin >> mat2;
		cout << mat2;

		mat2 = mat2 + mat1;

		cout << mat2;

		mat2 = mat2 - mat1;
		cout << mat2;

		mat2 = mat2 * mat1;
		cout << mat2;

		mat2 = mat2 / mat1;
		cout << mat2;
	}
#endif

#if 0
/*
1. By opening a MATLAB object in vc++ we can do anything inside vc++ with matlab program because its engine
is in our owenership.
2. This part dedicates to the cross vc++-MATLAB program. here we call matalb API for c++ 
in order to manipulate data and then prensent it in matlab.
3. reading matlab .mat file format data and manipulate it and feed it back to matlab 
and present it in MATLAB graphingvsystem. MATLAB has a very good graphing system.
4. we then will try to draw some of image processing data resulted from reconstruction draw using
directx of windows.

*/

	//open matlab engine
	Engine * m_pEngine;
	m_pEngine = engOpen("null");

	
	const int arraysize = 1000;
	const double degTorad = 0.174;

	double SinArray[arraysize];
	double CosArray[arraysize];
	double Degrees[arraysize];

	for (int iii = 0; iii < arraysize; iii++)
	{
		Degrees[iii] = iii;
		SinArray[iii] = sin(iii * degTorad);
		CosArray[iii] = cos(iii * degTorad);
	}

	cout << "Example 1 or 2 ? ";
	char sim = '1';
	cin >> sim;

	mxArray * SIN = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	memcpy((void*)mxGetPr(SIN), (void*) SinArray, sizeof(double) * arraysize);
	engPutVariable(m_pEngine, "SinGraph", SIN); //SinGraph is the alias name to refer to graph in matlab and matlab APIS FROM NOW ON:

	mxArray * COS = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	memcpy((void*)mxGetPr(COS), (void*)CosArray, sizeof(double) * arraysize);
	engPutVariable(m_pEngine, "CosGraph", COS);//CosGraph is the alias name to refer to graph in matlab and matalb APIS FROM NOW ON:

	mxArray * DEG = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	memcpy((void*)mxGetPr(DEG), (void*)Degrees, sizeof(double) * arraysize);
	engPutVariable(m_pEngine, "Degrees", DEG);

	engEvalString(m_pEngine, "figure( 'units','normalized','outerposition',[0 0 1 1]),");
	engEvalString(m_pEngine, "plot(Degrees, SinGraph, 'r', Degrees, CosGraph, 'b'), grid minor, title('Our Matlab Plot'), ");

	system("pause");

	//mathworks api to call in c++ to work with .mat matlab files
	matOpen("J:\\C++\\HL2027-3D Image Reconstruction and Analysis in Medicine\\Data---Sinogram\\SPECT dataset 1\\PROJ_PAT_4_2009_05_08.mat", "r");


	/*============================================================================*/
	//Multi-threading code snippet
	std::thread t(dosomething);
	t.join(); //dont forget to call this otherwise the worker thread does not call the function.

	std::vector<std::thread>  threads;
	//queue up the threads in a vector container
	for (int i = 1; i < 10; i++) threads.push_back(thread(count1m, i));
	ready = true;
	//fire each thread in orderly manner
	for (auto& th : threads) th.join();
	/*==============================================================================*/


	/*--------------------------RVALUE in c++11 code snippet-------------------------*/
	string s = "sohrab";
	string ms( std::move(s));
	cout << s << "  " << ms << endl;
	int && a = 1, b( move(a));
	cout << "a value is: " << a << " b value is: " << b << endl;
	b = 2;
	cout << "a value is: " << a << " b value is: " << b << endl;
	int x = 10;
	int& c = x;
	cout << "c value is: " << c << endl;
	int  d = move(c);
	cout << "c value is: " << c << "  " << "value of d is: " << d << endl;

//	int& lr1 = 10;     std::cout << lr1 << std::endl; // error
	int& lr2 = x;      std::cout << lr2 << std::endl; // ok
//	int& lr3 = foo();  std::cout << lr3 << std::endl; // error
	int& lr4 = bar();  std::cout << lr4 << std::endl; // ok
//	int& lr5 = baz();  std::cout << lr5 << std::endl; // error

	int&& rr1 = 10;    std::cout << rr1 << std::endl; // ok
//	int&& rr2 = x;     std::cout << rr2 << std::endl; // error
//	int&& rr3 = foo(); std::cout << rr3 << std::endl; // ok
//	int&& rr4 = bar(); std::cout << rr4 << std::endl; // error
	int&& rr5 = baz(); std::cout << rr5 << std::endl; // ERROR!?

	//class Movable contains a char buffer of size 512 and a size_t member that
	//stores the size of the character traits in it
	Movable m("This is a movable class constructor non-move one.");
	Movable&& m1 = Movable(m);
	Movable m2(m1);
	cout << "m object value is: " << m << endl;
	cout << "m1 object value is: " << m1 << endl;
	m1 = m2;
	cout << "m1 object value is: " << m1 << endl;
	cout << "m2 object value is: " << m2 << endl;

	/*====================================================================================*/
	//share_ptr och unique_ptr pointer templates
	shared_ptr<int> foo;	// foo is a lvalue
	shared_ptr<int> bar(new int(10));	//bar is a rvalue
	shared_ptr<int> third(bar);
	shared_ptr<double> fourth(new double, [](double * p) {delete p; }, allocator<int>());
	[&]() {*fourth = 10.202; weak_ptr<double> fifth(fourth); };

	cout << bar.use_count() << endl;
	cout << fourth.use_count() << endl;
	cout << foo.use_count() << endl;
	cout << third.use_count() << endl;

	*third = 2.003;
	shared_ptr<int> sixth(third);
	cout << "Sixth value is: " << *sixth << endl;
	shared_ptr<int> seventh = make_shared<int>(10);
	cout << "The value of seventh is: " << *seventh << endl;

	//i dont think this is necessary, after all we can 
	foo.reset(); bar.reset(); third.reset(); fourth.reset(); sixth.reset();
	seventh.reset();

	//runtime error because it is destroyed.
//	cout << "after calling sixth.reset(), sixth value is: " << *sixth << endl;

	//vector of unique_ptr pointers
	vector<unique_ptr<int>> arr_uniq;
	vector<unique_ptr<int>>::iterator itb, ite;

#define MAX 50
/*=====================================================================================*/
	//fill the vector with different values
	for(int i = 0; i < MAX; i++)	arr_uniq.push_back(unique_ptr<int>(new int(i*i)));
	itb = arr_uniq.begin(); ite = arr_uniq.end();
	//print them in entring order
	for (int i = 0; i < MAX; i++) cout << *arr_uniq[i] << " ";
	cout << endl;

	//sort the vector of values in reverse order
	int i(1);
	unique_ptr<int> tmp(new int(0));
	for (auto& p : arr_uniq) 
	{
		tmp = move(arr_uniq[arr_uniq.size()-i]);
		arr_uniq[arr_uniq.size()-i] = move(p);
		arr_uniq[i++ - 1] = move(tmp);
		if (--ite == ++itb)
			break; 
	}

	for (auto& p : arr_uniq) cout << *p << " ";
	cout << endl;
/*-----------------------------------------------------*/
	vector<shared_ptr<int>> arr_shared;
	for (int i = 0; i < MAX; i++) { shared_ptr<int> tmp(new int(i)); arr_shared.push_back(move(tmp)); }

	for_each(arr_shared.begin(), arr_shared.end(), [](shared_ptr<int> p) {cout << *p << " "; });

	cout << endl;
	vector<int> vec = { 0,1,2,3,4,5,6,7,8,9 };
	disp(vec, cout);
/*======================================================================*/
	//Uniform Initialization
	int mm = int();
	int mm1 = int{ 0 };
	int mm2(0);

	std::string str("Hello World.");
	std::string str1{ "Hello World." };
	std::string st2 = "Hello World.";

	//automatic type deduction: auto, decltype
	int tfoo = 0;
	auto tbar = tfoo;  //it it the same as: int bar = foo;
	decltype(tfoo) tbar1{0}; //it is the same at: int bar;
	cout << tbar1 + 10 << endl;

/*==================================================================================*/
	//c++ key words cor c++11
	/*
	alignas alignof asm and_eq and static_assert static_cast static_pointer_cast static bitand bitor break
	bool char char16_t char32_t class compl case catch const constexpr const_cast do double default
	dynamic_cast delete else continue extern decltype delegate export explicit enum false float for friend
	goto if inline int long mutable noexcept namespace new not_eq not nullptr or_eq protected private public
	register reinterpret_cast static static_cast switch short sizeof struct template this thread_local throw
	try static_assert true typeid typename typedef union unsigned using xor xor_eq while virtual void
	volatile
	*/
	//const object with mutable variable
	Mutable mut1;
	mut1.Modify_x_val(10);	//Modify_x_val is a const value of mut1 object yet i can modify
							//the contents of variables which are mutable like x value
	std::cout << mut1.show_x_val() << endl;
#endif
/*===========================================================================*/
	//constexpr is type specifier for literal types
	CONSTN<Countlower("Hello, world!")> out2; //template CONSTN takes a constexpr constructor and return number of lower order letters
											  //in the string constructor conststr
	cout << "conststr::foo(int newVal) is a constexpr static function call" << conststr::foo(66) << endl;
	//constexpr variable must be a literal type, intialized immediately, and all its constructors,
	//implicit conversions must be declared and defined as constexpr.
	constexpr double d0 = 2.0 / 1.0;
	cout << "d0 value is: " << d0 << endl;

	/*==========================  core constant expressions  ===========================================*/
	//a function call expression that calls a function or (constructor) that is not declared constexpr
	constexpr int n = std::numeric_limits<int>::max();// OK because max() is a constexpr function
//	constexpr int m = std::time(nullptr); //Error because it does not have const value, time is not declared constexpr

	//a function call expression that call a function or constructor that is declared constexpr but not defined.
	//No example for this one yet!
	constexpr int value = f(); //since f() is declared and defined at the beggining of this
	/*=====================================================================================*/
	//pointer calculations are undefined behavior therefore it is not permitted.
	int x1, y1, z[30];
//	constexpr auto e = &x1 - &y1; 
/*==========================================================================================*/
//	constexpr auto e = &z[20] - &z[3]; //pointer calculations are undefined behavior so 
										//they are not allowed.
	constexpr std::bitset<2> aaaa;
	constexpr bool bbb[2]{ 1,1 }; //if not initialized immediately then it is a UB situtation




	/*=====================  static_assert, is_trivial_constructible, is_copy_constructible ======*/
	/*
	static_assert is a compiler directive: meaning it allows you to check type information at compile time
	*/

	static_assert(std::is_trivial<X>::value, "X should be trivial");
	static_assert(std::is_pod<X>::value, "X should be POD.");

	static_assert(!std::is_trivial<Y>::value, "Y should not be trivial");
	static_assert(!std::is_pod<Y>::value, "Y should not be POD.");
//	static_assert(false, "I static_assert 'ed supervised"); //Error is issued in compile time.
/*----------------------------*/
	static_assert(std::is_copy_constructible<EX1>::value, "Ex1 is copy constructible");
	std::cout << "EX1 is copy constructible?  " << std::is_copy_constructible<EX1>::value << '\n'
		<< "EX1 is trivially copy constructible?  " << std::is_trivially_copy_constructible<EX1>::value << '\n' <<
		"EX2 is trivially copy constructible?  " << std::is_trivially_copy_constructible<EX2>::value << '\n'
		<< "EX2 is nothrow copy constructible? " << std::is_nothrow_copy_constructible<EX2>::value << '\n';

	//compile time error because EX1 type is not a trivially copy constructible type.
//	static_assert(std::is_trivially_copy_constructible<EX1>::value, "EX1 is not trivially copy constructible");

	/*==============Type Converisons using static_cast, dynamic_cast, reinterpret_cast, and etc. =========*/
	TypeConv tc1; //calls default ctor
	TypeConvB tc2 = tc1;  //calls ctor
	tc2 = tc1; //calls assignment
	tc1 = tc2; // calls type_cast operator

	/*========= Sort Algorithms such as: selection sort, shell sort, merge sort, quick sort ==================*/	
	SortingAlg::selection<double> so1;
	for (int i = 0; i < 10; i++) {
		so1.Add(std::rand());
	}
	std::cout << "Array before selection sort:" << endl;
	so1.show();
	so1.Sort();
	std::cout << "Array after selection sort:" << endl;
	so1.show();

	//graph processing
	/*construct a tiny Graph by reading the vertices and edges from a text file tinyG.txt*/
	Graph tinyG("tinyG.txt");
	int first(0), second(0);
	/* build a edge out of vertices*/
	for (int i = 0; i < tinyG.V(); i++){ first = tinyG.get_next(); second = tinyG.get_next(); 
				tinyG.AddEdge(first, second); }

	/*display an edge out of list of edges*/
	std::set<std::pair<int, int>>::iterator it = tinyG.E_begin();
	std::pair<int, int> pair = *it;
	std::cout << pair.first << " " << pair.second << std::endl;
	tinyG.adj(pair.first);
	/*build a list of adjacent vertices to a vertex*/
	std::set<std::pair<int, std::vector<int>>>::iterator a_it = tinyG.A_begin();
	for(int i = 0; i < a_it->second.size(); i++)
		std::cout << a_it->first << "----" << a_it->second[i] << endl;
	tinyG.Fill_adjMatrix();
	tinyG.show_adjMatrix(tinyG.V(), tinyG.V());

	pthread
	return 0;
}


/*

int& lr1 = 10;     // error: lvalue references rvalue
int& lr2 = x;      // ok
int& lr3 = foo1();  // error: lvalue references rvalue
int& lr4 = bar();  // ok
int& lr5 = baz();  // error: lvalue references rvalue

int&& rr1 = 10;    // ok
int&& rr2 = x;     // error: rvalue references lvalue
int&& rr3 = foo1(); // ok
int&& rr4 = bar(); // error: rvalue references lvalue
int&& rr5 = baz(); // ok

*/