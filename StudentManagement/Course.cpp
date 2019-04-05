#include "Course.h"

int Course::NumberOfWeek()
{
	stringstream d1(this -> startDate);
	stringstream d2(this -> endDate);
	string date;
	vector<int> sdate, edate;
	while (getline(d1, date, '/'))
	{
		sdate.push_back(stoi(date));
	}
	while (getline(d2, date, '/'))
	{
		edate.push_back(stoi(date));
	}
	tm stm = { 0, 0, 0, sdate[0], sdate[1] - 1, sdate[2] - 1900 };
	tm etm = { 0, 0, 0, edate[0], edate[1] - 1, edate[2] - 1900 };
	time_t x = mktime(&stm);
	time_t y = mktime(&etm);

	if (x != (time_t)(-1) && y != (time_t)(-1))
	{
		double dif = difftime(y, x) / (60 * 60 * 24);
		return abs(trunc(dif / 7));
	}

	return -1;
}
