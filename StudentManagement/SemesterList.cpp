#include "SemesterList.h"

bool SemesterList::importFromFile(string filename)
{
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) return 0;

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
		Semester sem;
		sem.no = stoi(row[0]);
		sem.name = row[1];
		sem.yearNo = stoi(row[2]);

		SemList.push_back(sem);
	}
	fin.close();
	return true;
}

bool SemesterList::exportToFile(string filename)
{
	ofstream fo;
	fo.open(filename);
	if (!fo.is_open()) return 0;
	for (int i = 0; i < (int)SemList.size(); ++i)
	{
		fo << SemList[i].no << ',';
		fo << SemList[i].name << ',';
		fo << SemList[i].yearNo << endl;
	}
	fo.close();
	return 1;
}

bool SemesterList::isExist(string name, int yearno)
{
	for (int i = 0; i < (int)SemList.size(); ++i)
	{
		if (SemList[i].matchYear(yearno))
		{
			if (SemList[i].matchName(name))
				return true;
			return false;
		}
	}
	return false;
}

bool SemesterList::addSemester(Semester & sem)
{
	if (isExist(sem.name, sem.yearNo)) return 0;
	sem.no = findNewNo();
	SemList.push_back(sem);
	exportToFile("SemesterList.txt");
	return false;
}

int SemesterList::findNewNo()
{
	if (SemList.size() == 0) return 1;
	int i = SemList.size() - 1;
	return (SemList[i].no + 1);
}

bool SemesterList::deleteSemester(int semesterno)
{
	for (int i = 0; i < (int)SemList.size(); ++i)
	{
		if (SemList[i].matchNo(semesterno))
		{
			SemList.erase(SemList.begin() + i);
			exportToFile("SemesterList.txt");
			return true;
		}
	}
	return false;
}

vector<Semester> SemesterList::getSemesterByYear(int yearno)
{
	vector<Semester> a;
	a.clear();
	for (int i = 0; i < (int)SemList.size(); ++i)
	{
		if (SemList[i].matchYear(yearno))
		{
			Semester b = SemList[i];
			a.push_back(b);
		}
	}
	return a;
}

