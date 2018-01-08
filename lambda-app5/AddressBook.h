#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class AddressBook
{
public:
	AddressBook();
	~AddressBook();

	template<typename Func>
	vector<string> FindAddress(Func func)
	{
		vector<string> result;
		for (auto iter = _Address.begin(); iter != _Address.end(); iter++)
		{
			if (func(*iter))
			{
				result.push_back(iter->c_str());
			}
		}
		return result;
	}


	vector<string> FindAddress2(function<bool (const string&)> func)
	{
		vector<string> result;
		for (auto iter = _Address.cbegin(); iter != _Address.cend(); iter++)
		{
			if (func(*iter))
			{
				result.push_back(iter->c_str());
			}
		}
		return result;
	}

private:
	vector<string> _Address;
};

