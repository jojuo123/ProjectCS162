#pragma once
#ifndef _Attendance_h_
#define _Attendance_h_

#include <iostream>
#include <string>
#include <vector>
#include "Global.h"
using namespace std;

struct Attendance
{
	int courseNo;
	int studentNo;
	string date;//dd/mm/yyyy
	char status[2];// (A/P)
};

#endif