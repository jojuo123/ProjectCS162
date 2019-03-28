#include "Semester.h"

bool Semester::matchYear(int anotheryearno)
{
	return (yearNo==anotheryearno);
}

bool Semester::matchName(string anothername)
{
	return (name==anothername);
}

bool Semester::matchNo(int anotherno)
{
	return (no==anotherno);
}
