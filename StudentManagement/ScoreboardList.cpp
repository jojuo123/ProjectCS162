#include "ScoreboardList.h"

bool ScoreboardList::ImportFromfile(string filename)
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
		Scoreboard sc;
		sc.courseNo = stoi(row[0]);
		sc.studentNo = stoi(row[1]);
		sc.lab = stoi(row[2]);
		sc.midterm = stoi(row[3]);
		sc.final = stoi(row[4]);
		sc.bonus = stoi(row[5]);

		Scorelist.push_back(sc);
	}
	fin.close();
	return true;
}

bool ScoreboardList::SaveToFile(string filename)
{
	ofstream fo;
	fo.open(filename);
	if (!fo.is_open()) return 0;
	for (int i = 0; i < (int)Scorelist.size(); ++i)
	{
		fo << Scorelist[i].courseNo << ',';
		fo << Scorelist[i].studentNo << ',';
		fo << Scorelist[i].lab << ',';
		fo << Scorelist[i].midterm << ',';
		fo << Scorelist[i].final << ',';
		fo << Scorelist[i].bonus << endl;
	}
	fo.close();
	return true;
}

bool ScoreboardList::AddOrUpdate(Scoreboard & sc)
{
	if (!sc.isValid()) return false;
	for (int i = 0; i < (int)Scorelist.size(); ++i)
	{
		/*if (Scorelist[i].courseNo == sc.courseNo && Scorelist[i].studentNo == sc.studentNo)
		{
			Scorelist[i].lab = sc.lab;
			Scorelist[i].midterm = sc.midterm;
			Scorelist[i].final = sc.final;
			Scorelist[i].bonus = sc.bonus;
			return true;
		}*/
		if (Scorelist[i].matchCourse(sc.courseNo) && Scorelist[i].matchStudent(sc.studentNo))
		{
			if (Scorelist[i].Update(sc))
			{
				SaveToFile("Scorelist.txt");
				return true;
			}
		}
	}
	Scorelist.push_back(sc);
	SaveToFile("Scorelist.txt");
	return true;
}

Scoreboard ScoreboardList::GetScoreboard(int stuno, int courseno)
{
	Scoreboard a;
	for (int i = 0; i < (int)Scorelist.size(); ++i)
	{
		if (Scorelist[i].studentNo == stuno && Scorelist[i].courseNo == courseno)
		{
			a = Scorelist[i];
			return a;
		}
	}
	a.courseNo = courseno;
	a.studentNo = stuno;
	a.lab = a.midterm = a.final = a.bonus = 0;
	return a;
}

bool ScoreboardList::ExportCsv(int courseno,string filename)
{
	ofstream fo;
	fo.open(filename);
	if (!fo.is_open()) return 0;
	StudentList a;
	a.importFromFile("student.txt");
	fo << "ID" << ',' << "Name" << ',' << "Lab" << ',' << "Midterm" << ',' << "Final" << ',' << "Bonus" << endl;
	for (int i = 0; i < (int)Scorelist.size(); ++i)
	{
		if (Scorelist[i].matchCourse(courseno))
		{
			Student b;
			a.GetStudentByNo(Scorelist[i].studentNo, b);
			fo << b.ID << ',' << b.firstName + b.lastName << ',' << Scorelist[i].lab << ',' << Scorelist[i].midterm << ','
				<< Scorelist[i].final << ',' << Scorelist[i].bonus << endl;
		}
	}
	fo.close();
	return true;
}

