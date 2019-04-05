
#ifndef FILE_H_
#define FILE_H_

#include <cstdio>
#include <Windows.h>
#include <iostream>
#include <cstring>
#include <conio.h>
#include <fstream>
#include "Class.h"
#include "Student.h"
#include "Course.h"
#include "CourseList.h"
#include "Lecturer.h"
#include "LecturerList.h"
#include "Scoreboard.h"
#include "Semester.h"
#include "Staff.h"
#include <vector>
#include <sstream>

using namespace std;

string eraseAllSlash(string str);

int importClassFile(string s);

bool importStudentFile(string s);

//Import from fileName (such as "18CTT1-courses.csv") into "list".
//Ignore header
//bool importCourse(string fileName, CourseList &courseList);
//Export from "list" into external file (such as "courses.txt");
//void exportCourse(string fileName, const CourseList &list);


#endif // !FILE_H_
