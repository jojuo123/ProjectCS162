#pragma once
#ifndef _SemesterList_h_
#define _SemesterList_h_
#include "Semester.h"
#include "AcademicYearList.h"
#include <fstream>
#include <sstream>

struct SemesterList
{
	vector<Semester> SemList;

	bool importFromFile(string filename);
	bool exportToFile(string filename);
	bool isExist(string name, int yearno);
	bool addSemester(Semester &sem);
	int findNewNo();//find no for new semester
	bool deleteSemester(int semesterno);
	vector<Semester> getSemesterByYear(int yearno);
	bool GetSemesterByNo(int no, Semester &sem);
};




#endif