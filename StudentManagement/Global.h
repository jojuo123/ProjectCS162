#pragma once
#ifndef _Global_h_
#define _Global_h_

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include "StudentList.h"
#include "Lecturer.h"
#include "LecturerList.h"
#include "Staff.h"
#include "StaffList.h"
#include "ClassList.h"
#include "AcademicYearList.h"
#include "SemesterList.h"
#include "AttendanceList.h"
#include "ScoreboardList.h"

using namespace std;
//struct Student;
//struct StudentList;
struct Global
{
	int currentRole;
	string username, password;
	Student currentStudent;
	StudentList stuList;
	LecturerList lecList;
	Lecturer currentLecturer;
	Staff currentStaff;
	StaffList staffList;
	ClassList classList;

	AcademicYearList academicYearList;
	SemesterList semesterList;
	ScoreboardList scoreboardList;

	bool currentlyLoggedIn;

	Global() {
		currentlyLoggedIn = false;
		staffList.importFromFile("staff.txt");
		lecList.importFromFile("lecturer.txt");
		stuList.importFromFile("student.txt");
		classList.importFromFile("class.txt");
	}
};


#endif
