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

using namespace std;
struct Student;
struct StudentList;
struct Global
{
	int currentRole;
	string username, password;
	Student currentStudent;
	StudentList stuList;
	LecturerList lecList;
	Lecturer currentLecturer;

	Global() {
		stuList.importFromFile("student.txt");
		lecList.importFromFile("lecturer.txt");
	}
};


#endif
