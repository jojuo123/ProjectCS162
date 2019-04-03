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
#include "AcademicYearList.h"
#include "SemesterList.h"

using namespace std;

#define TESTING_PHASE

void test() {
	{ //for testing importCourse and exportCourse
		/*
		CourseList cl;
		importCourse("18ctt5-courses.csv", cl);
		exportCourse("course.txt", cl);
		cl.courses.clear();
		importCourse("course.txt", cl);
		exportCourse("course2.txt", cl); */

		//for testing gotoxy
		/*
		gotoxy(1, 1); cout << "D";
		gotoxy(3, 5); cout << "M";
		gotoxy(2, 2); cout << "D";
		gotoxy(4, 4); cout << "M"; */

		//for testing resizeScreen
		//RESULT: IT DOES NOT AUTO-EXPAND THE SCREEN IF TOO LARGE TO FIT.
		//BUT IT DOES WHEN IT FIT THE SCREEN.
		/*
		resizeScreen(80, 52);
		Sleep(1000);
		resizeScreen(50, 40);
		Sleep(1000);
		resizeScreen(150, 52);
		Sleep(1000);
		resizeScreen(50, 40);
		*/

		/* { //for testing getlinePassword
			string password;
			gotoxy(1, 1);
			getlinePassword(password);
			cout << "You entered: " << password << endl;
		} //*/
		/*string username, password;
		Global a;
		cout << "Enter username and password: " << endl; cin >> username >> password;
		int num = a.lecList.Login(username, password);
		string newpass = "20122000";
		if (a.lecList.Update(num, newpass)) cout << "Changed" << endl;
		a.lecList.GetLecByNo(num, a.currentLecturer);
		cout << a.currentLecturer.ID << ' ' << a.currentLecturer.firstName << ' ' << a.currentLecturer.lastName << ' ';
		a.lecList.Remove(3);
		system("pause");*/
		/*AcademicYearList a;
		a.importFromFile("academicyear.txt");
	
		
		AcademicYear b; b.name = "hihi";
		a.AddYear(b);
		a.RemoveYear(3);*/
		SemesterList a;
		a.importFromFile("SemesterList.txt");
		Semester b;
		b.name = "Sem1";
		b.yearNo = 1;
		a.addSemester(b);
		a.deleteSemester(5);
		vector<Semester> c = a.getSemesterByYear(1);
		for (int i = 0; i < (int)c.size(); ++i)
		{
			cout << c[i].no<<" "<<c[i].name << " " << c[i].yearNo << endl;
		}
	}
}

int main()
{
#ifdef TESTING_PHASE
	test();
#else
	//Do real thing
	Global global;
	//startScreen();
	mainMenuScreen(global);
#endif
	return 0;
}