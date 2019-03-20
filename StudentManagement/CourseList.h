#ifndef _CourseList_h_
#define _CourseList_h_

#include "Course.h"

struct CourseList {
	vector<Course> courses;

	void AddCourse(Course c);
};

#endif