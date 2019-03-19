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
int staffMenu();
int lecturerMenu();
int studentMenu();
int roleSelectMenu();
int staffClassMenu ();
bool studentLoginScreen(string &username, string &password, Global &global);
void studentProfile(Global &global);


#endif // !SCREEN_H_
