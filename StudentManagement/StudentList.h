#pragma once
#ifndef _StudentList_h_
#define _StudentList_h_

#include "Student.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;
struct Global;
struct Student;

struct StudentList {
	vector<Student> students;
	string eraseAllSlash(string str);
	int Login(string username, string password);
	bool GetStudentByNo (int no, Student &stu);
	bool GetStudentByID(string ID, Student &stu);
	int findId();
	bool importFromFile (string filename);
	bool exportFile(string filename);
	bool AddStudent(Student stu);
	bool Update(int no, string newPassword);
	bool Remove(int no); //xoa 1 Stu	
	
};

#endif