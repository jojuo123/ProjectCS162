#pragma once
#ifndef _Staff_h_
#define _Staff_h_

#include <iostream>
#include <string>
#include "Course.h"
#include "Global.h"
using namespace std;

struct Staff
{
	int no;
	string ID;
	string name;
	string password;

	bool Login(string username, string password, Global &global);
	bool Update(Global &global, string newPassword, string newName);
};



#endif // !_Staff_h_
