#pragma once
#ifndef _Global_h_
#define _Global_h_

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"
#include "StudentList.h"

using namespace std;
struct Student;
struct StudentList;
struct Global
{
	int currentRole;
	string username, password;
	Student currentStudent;
	StudentList stuList;

	Global() {
		stuList.importFromFile("student.txt");
	}
};


#endif
