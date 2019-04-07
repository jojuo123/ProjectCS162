#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Global.h"
#include "FileManage.h"

using namespace std;

void TextColor(int x);
void gotoxy(int x, int y);
void resizeScreen(int width, int height);
void getlinePassword(string &password);


void startScreen();
int startMenu();
int roleSelectMenu();
int staffClassMenu ();
void studentProfile(Global &global);
bool staffLoginScreen(Global &global);
bool studentLoginScreen(Global &global);
bool staffChangePasswordScreen(Global &global);
bool studentChangePasswordScreen(Global &global);

void logout(Global &global);

//From this onward, is NEED-FURTHER-UPDATE section

//TESTED SECTION
int studentMenu(string firstName, string lastName);
int staffMenu(string firstName, string lastName);
int lecturerMenu(string firstName, string lastName);
bool lecturerLoginScreen(Global &global);
bool lecturerChangePasswordScreen(Global &global);
int mainMenuScreen(Global &global);

//void lecturerProfile(Global &global); //STALLED, WAIT FOR BACK-END FOR LIST-ALL-COURSES-WHICH-ARE-TAUGHT METHOD.
void studentRemoveScreen(Global &global); //Staff only.
void studentEditScreen(Global &global);
bool isValidDoB(string dob);
bool isLeapYear(int year);

void studentImportFromCSVScreen(Global &global);
void studentAddScreen(Global &global);
void studentChangeClassScreen(Global &global);

void classListScreen(Global &global);
void classStudentListScreen(Global &global); //feature 12

void academicYearScreenUtil(Global &global, int baseY);
void academicYearCreateScreen(Global &global);
void academicYearDeleteScreen(Global &global);
int academicYearSelectScreen(Global &global, string IntroText = "");

void semesterCreateScreen(Global &global);
void semesterDeleteScreen(Global &global);
void semesterListScreen(Global &global);
int semesterSelectScreen(Global &global, string IntroText = "");

void courseImportFromCSVScreen(Global &global);
void courseAddScreen(Global &global);

void courseEditScreen(Global &global);
void courseRemoveScreen(Global &global);

void courseStudentRemoveScreen(Global &global);
void courseStudentAddScreen(Global &global);

void semesterListAllCourseScreenUtil(Global &global, vector<Course> &courseVec, int &semNo, string IntroText = "", bool getch = true);
void semesterListAllCourseScreen(Global &global);
void courseListAllStudentScreen(Global &global);

void lecturerAddScreen(Global &global); //staff only
void lecturerListScreen(Global &global); 

void courseViewAttendanceListScreenUtil(Global &global, Course selectedCourse, bool getch=true);
void courseViewAttendanceListScreen_staff(Global &global);

void courseViewScoreboardScreen(Global &global); //feature 24,25

#endif // !SCREEN_H_
