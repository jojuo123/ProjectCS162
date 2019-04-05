#include "Attendance.h"

bool Attendance::matchCourseNo(int anothercno)
{
	return courseNo == anothercno;
}

bool Attendance::matchStudentNo(int anothersno)
{
	return studentNo == anothersno;
}

bool Attendance::matchweekNo(int anotherwno)
{
	return weekNo == anotherwno;
}