#pragma once
#ifndef _Lecturer_h_
#define _Lecturer_h_

#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
using namespace std;

struct Lecturer
{
	int no;
	string ID;
	string password;
	string firstName;
	string lastName;
    vector<Course> course;

	//bool Login(string username, string password, Global &global);
	//bool Update(Global &global, string newPassword, string newName);
	vector<Course> GetCoursesList();

	bool matchNo(int anotherNo);
	bool matchID(string anotherId);
	
};

#endif
