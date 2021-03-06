#include"AttendanceList.h"
using namespace std;

bool AttendanceList::importFromFile(string filename)
{
	ifstream fin; fin.open(filename);
	if (!fin.is_open()) return 0;

	attendances.clear();

	string line, word;
	vector<string> row;

	//getline(fin, line);

	while (getline(fin, line))
	{
		if (line.length() == 0) break;
		row.clear();

		stringstream s(line);

		while (getline(s, word, ','))
		{
			row.push_back(word);
		}
		Attendance att;
		
		att.weekNo = stoi(row[0]);
		att.courseNo = stoi(row[1]);
		att.studentNo = stoi(row[2]);
		att.status = row[3];

		attendances.push_back(att);
	}
	fin.close();
	return 1;
}
bool AttendanceList::exportFile(string filename)
{
	ofstream fout;
	fout.open(filename);

	for (unsigned int i = 0; i < (int)attendances.size(); i++)
	{
		
		fout << attendances[i].weekNo << ",";
		fout << attendances[i].courseNo << ",";
		fout << attendances[i].studentNo << ",";
		fout << attendances[i].status <<endl;
	}

	fout.close();
	return true;
}
string AttendanceList::getAttendance(int weekNo, int courseNo, int studentNo, Attendance& att)
{
	for (unsigned int i = 0; i < (int)attendances.size(); ++i) {
		if (attendances[i].matchweekNo(weekNo) && attendances[i].matchCourseNo(courseNo) && attendances[i].matchStudentNo(studentNo))
		{
			att = attendances[i];
			return attendances[i].status;
		}
	}
	return "A";
}
void AttendanceList::addOrUpdateAttendance(int weekNo, int courseNo, int studentNo, string status)
{

	for (unsigned int i = 0; i < (int)attendances.size(); ++i) {
		if (attendances[i].matchweekNo(weekNo) && attendances[i].matchCourseNo(courseNo) && attendances[i].matchStudentNo(studentNo))
		{
			attendances[i].status = status;
			exportFile("attendance.txt");
			return;
		}
	}
	Attendance att;
	att.weekNo = weekNo;
	att.courseNo = courseNo;
	att.studentNo = studentNo;
	att.status = status;

	attendances.push_back(att);
	exportFile("attendance.txt");
	return;
}

void AttendanceList::exportToFileCSV(string filename, StudentList & stuList, int courseNo, CourseList &cList, CourseStudentList &cstuList)
{
	ofstream fout;
	fout.open(filename);
	
	Course c;
	if (cList.GetCourseByNo(courseNo, c))
	{
		Student stu;
		int weeks = c.NumberOfWeek();
		
		fout << "Student Id,";
		for (int i = 1; i < weeks; i++)
			fout << "Week " << i << ",";
		fout << "week " << weeks << endl;

		vector<Student> list;
		if (cstuList.GetStudentOfCourse(courseNo, list, stuList, cList))
		{
			for (int i = 0; i < (int)list.size(); i++)
			{
				fout << list[i].ID << ",";
				for (int j = 1; j < weeks; ++j)
				{
					Attendance att;
					fout << getAttendance(j, courseNo, list[i].no, att) << ",";
				}
				Attendance att;
				fout << getAttendance(weeks, courseNo, list[i].no, att) << endl;
			}
		}
	}

	fout.close();
}
