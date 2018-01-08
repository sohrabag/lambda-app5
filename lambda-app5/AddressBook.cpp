#include "stdafx.h"

#include "AddressBook.h"

AddressBook::AddressBook()
{
	_Address.push_back("first.org");
	_Address.push_back("second.org");
	_Address.push_back("Third.org");
	_Address.push_back("fourth.net");
	_Address.push_back("fifth.net");
}

AddressBook::~AddressBook()
{
	//delete all of the address from address book
	_Address.clear();
}

