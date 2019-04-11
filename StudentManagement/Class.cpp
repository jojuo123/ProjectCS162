#include"Class.h"

bool Class::matchClass(string anotherclassname)
{
	return ((name.size() == anotherclassname.size()) && 
		equal(name.begin(), name.end(), anotherclassname.begin(), [](char & c1, char & c2){
		return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
	}));
}

bool Class::matchNo(int anotherno)
{
	return anotherno == no;
}
