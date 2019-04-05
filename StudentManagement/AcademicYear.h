#pragma once
#ifndef _AcademicYear_h_
#define _AcademicYear_h_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct AcademicYear
{
	int no;
	string name;

	bool matchNo(int anotherno);
	bool matchName(string anothername);
	//vector<Semester> semesters;
};
#endif // !
