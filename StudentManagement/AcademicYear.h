#pragma once
#ifndef _AcademicYear_h_
#define _AcademicYear_h_

#include <iostream>
#include <string>
#include <vector>
#include "Semester.h"
#include "Global.h"
using namespace std;

struct AcademicYear
{
	int no;
	string name;
	vector<Semester> semesters;
};
#endif // !
