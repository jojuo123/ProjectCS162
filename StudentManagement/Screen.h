#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Global.h"

using namespace std;

void TextColor(int x);
void startScreen();
int startMenu();
int staffMenu();
int lecturerMenu();
int studentMenu();
int roleSelectMenu();
int staffClassMenu ();
bool studentLoginScreen (string &username, string &password, Global &global);


#endif // !SCREEN_H_
