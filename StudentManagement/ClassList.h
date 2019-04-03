#ifndef _ClassList_h_
#define _ClassList_h_

#include "Class.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
struct ClassList {
	vector<Class> classes;

	bool addClass(Class cla);
	bool getClassByNo(int no, Class&cla);
	bool getClassByName(string name, Class&cla);
	bool importFromFile(string filename);
	bool exportFile(string filename);
	bool remove(int no);
	int count();
};


#endif