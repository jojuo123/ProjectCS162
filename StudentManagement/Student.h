#pragma once
#ifndef _Student_h_
#define _Student_h_

#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Global.h"
using namespace std;

struct Course;

struct Student
{
	int no;
	string ID;
	string password;
	string firstName;
	string lastName;
	char gender[2];
	string DoB; //dd/mm/yyyy
	int classID;
	vector<Course> course;

	bool Login(string username, string password, Global &global);
	bool Update(Global &global, string newPassword, string newFirstName, string newLastName, char newGender, string newDOB, int newClassNo);
	vector<Course> GetCoursesList();
};

#endif