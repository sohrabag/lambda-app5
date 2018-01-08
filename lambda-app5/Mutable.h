#pragma once
#include <iostream>
#include <stdexcept>

/*
Mutable member variable of an constant object can be modified despite its parent object is oonstant
*/
class Mutable
{
	mutable int _x;
	int _y;

public:
	Mutable();
	~Mutable();

	void Modify_x_val(int newVal) const { _x += newVal; /*_y += newVal;*/ }
	int show_x_val() { return _x; }
};

//literal class type
class conststr {
	const char* p;
	std::size_t	size;

public:
	template<std::size_t N>
		constexpr conststr(const char(&a)[N]) : size(N), p(a){}
		constexpr char operator[](std::size_t n) const {
			return n < size ? p[n] : throw std::out_of_range("");
		}
		constexpr std::size_t Size() const { return size; }
		constexpr static int foo(int newVal) { return 2; } //constexpr function declared and defined as static functions
};

