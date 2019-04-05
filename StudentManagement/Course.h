#ifndef _Course_h_
#define _Course_h_

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

struct Student;
//typedef vector<Student> vecstu;

struct Course
{
	int no;
	string ID;
	string name;

	int lecturerNo;
	//string lecturerAccount;

	string startDate;//dd/mm/yyyy
	string endDate;
	string dayOfWeek;// Mon,Tues,...
	string startHour;//hh:mm
	string endHour;
	string room;

	int classNo;
	int SemNo;
	//string className;

	//bool Update(Global &global, Course newInformation);
	//bool RemoveStudent(int stuNo);
	//bool AddStudent(int studentNo);
	//bool RemoveStudent(string stuId);
	//bool AddStudent(string studentId);
	int NumberOfWeek();
};

#endif