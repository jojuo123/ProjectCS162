#ifndef _CourseList_h_
#define _CourseList_h_

#include "Course.h"
#include "LecturerList.h"
#include "ClassList.h"

struct CourseList {
	vector<Course> courses;

	void AddCourse(Course c);
	bool importFromFileCSV(string fileName, ClassList &classRef, LecturerList &lecRef, int semNo);
	bool exportFile(string fileName);
	bool importFromFile(string filename);
	bool getCourseOfLecturer(int LecNo, vector<Course> &list);
	bool Update(int no, Course course);
	bool GetCourseById(string id, Course &course);
	bool GetCourseByNo(int no, Course &course);
	int FindNo();
	bool Remove(int no);
};

#endif