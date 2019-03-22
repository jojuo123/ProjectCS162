#include "Lecturer.h"

bool Lecturer::matchNo(int anotherNo)
{
	if (no == anotherNo) return true;
	return false;
}

bool Lecturer::matchID(string anotherId)
{
	if (ID == anotherId) return true;
	return false;
}

