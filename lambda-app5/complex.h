#pragma once
#include <ostream>

using namespace std;

class complex
{
public:
	complex() {}
	~complex() {}
	complex(double Img, double real) : _Img(Img), _real(real) {}
	complex(const complex& obj)
	{
		_Img = obj._Img; _real = obj._real;
	}
	friend ostream& operator<<(ostream& out, complex c);

	//methods and operators

	complex operator+(const complex& other)
	{
		_Img += other._Img;
		_real += other._real;

		return complex(_Img, _real);
	}

	void print() { [&]() { cout << "_Img value is: " << _Img << "----" << "_real value is: " << _real << endl; }(); };

private:
	double _Img;
	double _real;
};

//this is a friend function which has access to classified data in the class.
ostream& operator<<(ostream& out, complex c)
{
	out << "Real part: " << c._real << "\n";
	out << "Imaginary part: " << c._Img << "\n";

	return out;
}