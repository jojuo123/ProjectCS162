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
#include "Screen.h"

using namespace std;

//#define TESTING_PHASE

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
#endif
	//Do real thing
	Global global;
	for (global.currentRole = roleSelectMenu(); global.currentRole<1 || global.currentRole>3; global.currentRole=roleSelectMenu());
	if (global.currentRole == 3) { //student
		bool x = studentLoginScreen(global.username, global.password, global);
		if (x) {
		if(	studentMenu()==5)
			studentProfile(global);//test
		}
		else {
			cout<<"Login failed.";
		}
	}

	importStudentFile("18CTT5.csv");
	return 0;
}