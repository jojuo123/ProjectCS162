#include "Scoreboard.h"

bool Scoreboard::matchCourse(int anothercouseno)
{
	return (courseNo == anothercouseno);
}

bool Scoreboard::matchStudent(int stuno)
{
	return (studentNo == stuno);
}

bool Scoreboard::Update(Scoreboard & anothersc)
{
	lab = anothersc.lab;
	midterm = anothersc.midterm;
	final = anothersc.final;
	bonus = anothersc.bonus;
	return true;

}

bool Scoreboard::isValid()
{
	if ((0 <= lab && lab<= 10) &&( 0 <= midterm && midterm <= 10) && (0 <= final && final <= 10) &&( 0 <= bonus && bonus <= 10))
		return true;
	return false;
}
