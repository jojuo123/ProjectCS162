#pragma once
#ifndef _Attendance_h_
#define _Attendance_h_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Attendance
{
	int courseNo;
	int studentNo;
	int weekNo;
	bool matchCourseNo(int anothercno);
	bool matchStudentNo(int anothersno);
	bool matchweekNo(int anotherwno);
	//string date;//dd/mm/yyyy
	string status;// (A/P)
};

#endif