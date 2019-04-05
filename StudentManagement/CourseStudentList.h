#ifndef COURSE_STUDENT_LIST_H
#define COURSE_STUDENT_LIST_H

#include "CourseStudent.h"
#include "Student.h"
#include "StudentList.h"
#include "Course.h"
#include "CourseList.h"
#include <vector>
#include <sstream>
#include <fstream>

struct CourseStudentList
{
	vector<CourseStudent> courseStudents;

	bool AddStudentToCourse(int noCourse, int noStudent);
	bool GetStudentOfCourse(int noCourse, vector<Student> &list, StudentList &stuList, CourseList &cList); 
	bool GetCoursesOfStudent(int noStudent, vector<Course> &list, CourseList &cList, StudentList &stuList);
	bool Remove(int noCourse, int noStudent);
	bool SaveToFile(string filename);
	bool ImportFromFile(string filename);
};

#endif // !COURSE_STUDENT_LIST_H

