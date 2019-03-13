#pragma once
#ifndef _Semester_h_
#define _Semester_h_

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"
using namespace std;

struct Semester
{
	int no;
	string name;
	int yearNo;
	vector<Course> courses;
};

#endif