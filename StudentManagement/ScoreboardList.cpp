#include "ScoreboardList.h"
#include <iomanip>

bool ScoreboardList::ImportFromfile(string filename)
{
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) return 0;
	Scorelist.clear();
	string line, word;
	vector<string> row;
	while (getline(fin, line))
	{
		if (line.length() == 0) break;
		row.clear();
		stringstream s(line);
		while (getline(s, word, ','))
		{
			row.push_back(word);
		}
		Scoreboard sc;
		sc.courseNo = stoi(row[0]);
		sc.studentNo = stoi(row[1]);
		sc.lab = stod(row[2]);
		sc.midterm = stod(row[3]);
		sc.final = stod(row[4]);
		sc.bonus = stod(row[5]);

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
	CourseList cList;
	cList.importFromFile("course.txt");
	fo << "ID" << ',' << "First name"<<','<<"Last name"<< ',' << "Lab" << ',' << "Midterm" << ',' << "Final" << ',' << "Bonus" << endl;
	/*
	for (int i = 0; i < (int)Scorelist.size(); ++i)
	{
		if (Scorelist[i].matchCourse(courseno))
		{
			Student b;
			a.GetStudentByNo(Scorelist[i].studentNo, b);
			fo << b.ID << ',' << b.firstName<<','<<b.lastName << ',' << Scorelist[i].lab << ',' << Scorelist[i].midterm << ','
				<< Scorelist[i].final << ',' << Scorelist[i].bonus << endl;
		}
	}*/
	CourseStudentList cstuList;
	cstuList.ImportFromFile("coursestudent.txt");
	vector<Student> list;
	if (cstuList.GetStudentOfCourse(courseno, list, a, cList))
	{
		fo << fixed << setprecision(2);
		for (int i = 0; i < (int)list.size(); i++)
		{
			fo << list[i].ID << "," << list[i].firstName << "," << list[i].lastName << ",";
			Scoreboard sc;
			sc = GetScoreboard(list[i].no, courseno);
			
			fo << sc.lab << "," << sc.midterm << "," << sc.final << "," << sc.bonus << endl;
		}
		fo << setprecision(0);
	}
	fo.close();
	return true;
}

bool ScoreboardList::ImportFromCSV(string filename, int courseNo, StudentList & stuList)
{
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) return 0;

	string line, word;
	vector<string> row;

	getline(fin, line);

	while (getline(fin, line))
	{
		if (line.length() == 0)
			break;
		stringstream s(line);
		row.clear();
		while (getline(s, word, ','))
		{
			
			row.push_back(word);
		}
		Scoreboard tmp;
		Student a;
		if (stuList.GetStudentByID(row[0], a))
		{
			tmp.courseNo = courseNo;
			tmp.studentNo = a.no;
			tmp.lab = stod(row[3]);
			tmp.midterm = stod(row[4]);
			tmp.final = stod(row[5]);
			tmp.bonus = stod(row[6]);
			AddOrUpdate(tmp);
		}

	}
	fin.close();
	return true;
}

