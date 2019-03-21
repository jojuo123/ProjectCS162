#pragma once
#ifndef _LecturerList_h_
#define _LecturerList_h_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Lecturer.h"
using namespace std;

struct LecturerList
{
	vector<Lecturer> lecturers; ///VS2013 khong cho trung voi ten struct

	bool importFromFile(string filename);
	int findId(string ID);
	int Login(string username, string password);
	bool GetLecByNo(int no, Lecturer &lec);
	bool GetLecByID(string ID, Lecturer &lec);
	bool Update(int no, string newpassword);//chi doi password
	bool exportFile(string filename);
	bool Remove(int no);
	bool addLecturer(Lecturer &lec);

};
#endif // !_Lecturer_h_

