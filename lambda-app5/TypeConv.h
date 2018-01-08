#pragma once
class TypeConv
{
public:

	TypeConv()
	{
		std::cout << "calls ctor from within TypeConv class" << endl;
	}

	virtual ~TypeConv()
	{
		std::cout << "calls dtor from within TypeConv class" << endl;
	}
};

class TypeConvB{
public:
	TypeConvB(TypeConv& typeconv) { std::cout << "Conversion from TypeConv (constructor)" << endl; }
	TypeConvB& operator=(const TypeConv& typeconv) { std::cout << "Conversion from TypeConv Assignment" << endl; return *this; }
	operator TypeConv() { std::cout << "Conversion from TypeConv (default-cast operator)" << endl; return TypeConv(); }
};

