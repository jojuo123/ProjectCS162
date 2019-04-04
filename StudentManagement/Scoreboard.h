#pragma once
#ifndef _Scoreboard_h_
#define _Scoreboard_h_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Scoreboard
{
	int courseNo;
	int studentNo;
	double lab;
	double midterm;
	double final;
	double bonus;

	bool matchCourse(int anothercouseno);
	bool matchStudent(int stuno);
	bool Update(Scoreboard &anothersc);
	bool isValid();

};


#endif