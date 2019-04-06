#pragma once
#ifndef _AttendanceList_h_
#define _AttendanceList_h_
#include"Attendance.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "Student.h"
#include "Course.h"
#include "CourseList.h"
#include "StudentList.h"
#include "CourseStudent.h"
#include "CourseStudentList.h"

using namespace std;
struct AttendanceList
{
	vector<Attendance> attendances;
	bool importFromFile(string filename);
	bool exportFile(string filename);
	string getAttendance(int weekNo, int courseNo, int studentNo, Attendance& att);
	void addOrUpdateAttendance(int weekNo, int courseNo, int studentNo, string status);
	void exportToFileCSV(string filename, StudentList &stuList, int courseNo, CourseList &cList, CourseStudentList &cstuList );
};
#endif
