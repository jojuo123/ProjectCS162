#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void TextColor(int x);
void startScreen();
int startMenu();
int staffMenu();
int lecturerMenu();
int studentMenu();
int roleSelectMenu();
int staffClassMenu ();

#endif // !SCREEN_H_