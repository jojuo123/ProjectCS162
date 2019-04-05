#include "CourseStudent.h"

bool CourseStudent::Match(int courseNo, int studentNo)
{
	return (this->CourseNo == courseNo && this->StudentNo == studentNo);
}
