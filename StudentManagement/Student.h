#pragma once
#ifndef _Student_h_
#define _Student_h_

#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
//#include "Global.h"
using namespace std;

struct Course;

struct Student
{
	int no;
	string ID;
	string password;
	string firstName;
	string lastName;
	char gender;
	string DoB; //dd/mm/yyyy
	int classID;
	vector<Course> course;

	
	//bool Update(string newPassword, string newFirstName, string newLastName, char newGender, string newDOB, int newClassNo);
	vector<Course> GetCoursesList();

	bool matchNo (int anotherNo);
};

#endif