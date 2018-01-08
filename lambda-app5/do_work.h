#pragma once

#include <iostream>
#include <thread>

using namespace std;

class do_work
{
public:

	do_work()
	{
	}

	virtual ~do_work()
	{
	}

	void operator()();
	void dosomething();
};

inline void do_work::operator()() {
	dosomething();
}

inline void do_work::dosomething() {
	cout << "A worker function is called from within a thread." << endl;
}

