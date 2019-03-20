#ifndef _ClassList_h_
#define _ClassList_h_

#include "Class.h"

struct ClassList {
	vector<Class> classes;

	//find the classNo of the name in the list.
	int ClassNo(string ClassName);
};

