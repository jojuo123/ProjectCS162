#ifndef COURSE_STUDENT_H
#define COURSE_STUDENT_H

#include "Student.h"
#include "StudentList.h"
#include "Course.h"
#include "CourseList.h"

struct CourseStudent
{
	int CourseNo;
	int StudentNo;

	bool Match(int courseNo, int studentNo);
	CourseStudent()
	{

	}
	CourseStudent(int _courseNo, int _studentNo)
	{
		this->CourseNo = _courseNo;
		this->StudentNo = _studentNo;
	}
};

#endif // !COURSE_STUDENT_H

