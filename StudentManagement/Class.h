#pragma once
#ifndef _Class_h_
#define _Class_h_

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"
#include "Global.h"
using namespace std;

struct Class
{
	int no;
	string name;
	vector<Student> students;

	bool matchClass(string anotherClassName);
};

struct ClassList {
	vector<Class> classes;

	//find the classNo of the name in the list.
	int ClassNo(string ClassName);
};


#endif