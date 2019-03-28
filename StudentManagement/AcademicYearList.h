#pragma once
#ifndef  _AcademicYearList_h_
#define  _AcademicYearList_h_
#include "AcademicYear.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct AcademicYearList
{
	vector<AcademicYear> AcademicYears;

	bool importFromFile(string filename);
	bool AddYear(AcademicYear &year);
	int GetYearNoByName(string name);
	bool GetYearByNo(int no, AcademicYear &year);
	bool isExist(string name);//kt xem da co nam do chua
	int findNewNo();// tim no cua new year dc them vao
	bool RemoveYear(int yearno);
	bool ExportFile(string filename);
};




#endif // ! _AcademicYearList_h_
