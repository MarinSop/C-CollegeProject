#pragma once
#include <string>
struct UserData
{
	UserData(void* p,std::string str)
	{
		pointer = p;
		data = str;
	}
	void* pointer;
	std::string data;
};

