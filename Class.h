#pragma once
#ifndef _Class_h_
#define _Class_h_

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"
using namespace std;

struct Class
{
	int no;
	string name;
	//vector<Student> students;

	bool matchClass(string anotherClassName);
	bool matchNo(int anotherno);
};


#endif