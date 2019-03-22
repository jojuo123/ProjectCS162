#pragma once
#ifndef _Staff_h_
#define _Staff_h_

#include <iostream>
#include <string>
#include "Course.h"
using namespace std;

struct Staff
{
	int no;
	string ID;
	string name;
	string password;

	bool matchNo(int anotherNo);
};



#endif // !_Staff_h_

