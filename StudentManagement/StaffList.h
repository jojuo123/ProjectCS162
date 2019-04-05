#pragma once
#ifndef _StaffList_h_
#define _StaffList_h_

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Staff.h"

using namespace std;

struct StaffList {
	vector<Staff> staffs;
	int Login(string username, string password);
	bool GetStafftByNo(int no, Staff &sta);
	bool importFromFile(string filename);
	bool Update(int no, string newPassword);
	bool exportFile(string filename);
};

#endif