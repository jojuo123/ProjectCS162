#pragma once
#ifndef _Global_h_
#define _Global_h_

#include <iostream>
#include <string>
#include <vector>

#include "Student.h"
#include "StudentList.h"

#include "Staff.h"
#include"StaffList.h"

using namespace std;
struct Student;
struct StudentList;
struct Staff;
struct StaffList;
struct Global
{
	int currentRole;
	string username, password;
	//Student
	Student currentStudent;
	StudentList stuList;
	//Staff
	Staff currentStaff;
	StaffList staList;
	Global() {
		stuList.importFromFile("student.txt");
		staList.importFromFile("staff.txt");
	}
};


#endif
