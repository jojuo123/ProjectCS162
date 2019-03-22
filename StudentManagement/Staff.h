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

	//bool Login(string username, string password, Global &global);
	//bool Update(Global &global, string newPassword, string newName);
	bool matchNo(int anotherNo);
};



#endif // !_Staff_h_

