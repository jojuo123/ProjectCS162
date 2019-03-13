#include <cstdio>
#include <Windows.h>
#include <iostream>
#include <cstring>
#include <conio.h>
#include <fstream>
#include "Class.h"
#include "Course.h"
#include "Student.h"
#include "Lecturer.h"
#include "Global.h"
#include "LecturerList.h"
#include "Scoreboard.h"
#include "Semester.h"
#include "Staff.h"
#include <vector>
#include <sstream>
#include "FileManage.h"

using namespace std;

#define TESTING_PHASE

void test() {
	{ //for testing importCourse and exportCourse
		CourseList cl;
		importCourse("18ctt5-courses.csv", cl);
		exportCourse("course.txt", cl);
		cl.courses.clear();
		importCourse("course.txt", cl);
		exportCourse("course2.txt", cl);
	}
}

int main()
{
#ifdef TESTING_PHASE
	test();
#elif
	//Do real thing
#endif
	//importStudentFile("18CTT5.csv");
	return 0;
}