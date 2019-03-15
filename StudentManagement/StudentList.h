#pragma once
#ifndef _StudentList_h_
#define _StudentList_h_

#include "Student.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
struct Global;
struct Student;

struct StudentList {
	vector<Student> students;
	int Login(string username, string password);
	bool GetStudentByNo (int no, Student &stu);
	bool importFromFile (string filename);
};

#endif