#pragma once

#include <iostream>
#include "Iter2.h"

class IntVector
{
public:

	IntVector();
	~IntVector();

	//methods
	Iter2 begin() const;
	Iter2 end() const;
	int get(int pos) const;
	void set(int pos, int val);


private:
	int _data[100];
};
