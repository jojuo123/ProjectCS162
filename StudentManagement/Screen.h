#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Global.h"

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

//NOT TESTED SECTION
//void lecturerProfile(Global &global); //STALLED, WAIT FOR BACK-END FOR LIST-ALL-COURSES-WHICH-ARE-TAUGHT METHOD.
void removeStudentScreen(Global &global); //Staff only.
void editStudentScreen(Global &global);
bool isValidDoB(string dob);
bool isLeapYear(int year);

#endif // !SCREEN_H_
