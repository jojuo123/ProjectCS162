#include "AcademicYearList.h"

bool AcademicYearList::importFromFile(string filename)
{
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) return 0;

	AcademicYears.clear();

	string line, word;
	vector<string> row;
	while (getline(fin, line))
	{
		row.clear();
		stringstream s(line);
		while (getline(s, word, ','))
		{
			row.push_back(word);
		}
		AcademicYear year;
		year.no = stoi(row[0]);
		year.name = row[1];

		AcademicYears.push_back(year);
	}
	fin.close();
	return true;
}

bool AcademicYearList::AddYear(AcademicYear & year)
{
	if (isExist(year.name))
		return false;
	year.no = findNewNo();
	AcademicYears.push_back(year);
	ExportFile("academicyear.txt");
	return true;
}

int AcademicYearList::GetYearNoByName(string name)
{
	for (int i = 0; i < (int)AcademicYears.size(); ++i)
	{
		if (AcademicYears[i].matchName(name) == true)
		{
			return AcademicYears[i].no;
		}
	}
	return -1;
}

bool AcademicYearList::GetYearByNo(int no, AcademicYear & year)
{
	for (int i = 0; i < (int)AcademicYears.size(); ++i)
	{
		if (AcademicYears[i].matchNo(no) == true)
		{
			year = AcademicYears[i];
			return true;
		}
	}
	return false;
}

bool AcademicYearList::isExist(string name)
{
	for (int i = 0; i < (int)AcademicYears.size(); ++i)
	{
		if (AcademicYears[i].matchName(name))
		{
			return true;
		}
	}
	return false;
}

int AcademicYearList::findNewNo()
{
	if (AcademicYears.size() == 0)
		return 1;
	int i = AcademicYears.size() - 1;
	return (AcademicYears[i].no + 1);
}

bool AcademicYearList::RemoveYear(int yearno)
{
	for (int i = 0; i < (int)AcademicYears.size(); ++i)
	{
		if (AcademicYears[i].matchNo(yearno))
		{
			AcademicYears.erase(AcademicYears.begin() + i);
			ExportFile("academicyear.txt");
			return true;
		}
	}
	return false;
}

bool AcademicYearList::ExportFile(string filename)
{
	ofstream fo;
	fo.open(filename);
	if (!fo.is_open()) return 0;
	for (int i = 0; i <(int) AcademicYears.size(); ++i)
	{
		fo << AcademicYears[i].no << ',';
		fo << AcademicYears[i].name << endl;
	}
	fo.close();
	return true;
}
