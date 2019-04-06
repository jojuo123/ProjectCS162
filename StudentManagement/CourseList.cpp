#include "CourseList.h"

void CourseList::AddCourse(Course c) {
	c.no = FindNo();
	courses.push_back(c);
	
	exportFile("course.txt");
}


bool CourseList::importFromFileCSV(string fileName, ClassList &classRef, LecturerList &lecRef, int semNo) {
	FILE *fin = fopen(fileName.c_str(), "r");
	if (fin == NULL) return 0;
	char buf[1000], cid[20], cname[100], classstr[20], lecacc[40], stdate[11], eddate[11],
		dow[5], sthour[10], edhour[10], room[10];
	int cno;
	fgets(buf, 1000, fin); //ignore first line.
	do {
		fgets(buf, 1000, fin);
		if (feof(fin)) break;
		Course c;
		sscanf(buf, "%d,%[^,],%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,\n]", &cno, cid, cname, classstr, lecacc, stdate, eddate, dow, sthour, edhour, room);
		{ //This may need change in future.
			c.no = cno;
			c.ID = cid;
			c.name = cname;

			string className = classstr;
			Class cc;
			if (classRef.getClassByName(className, cc)) {

			}
			else {
				cc.name = className;
				classRef.addClass(cc);
				classRef.getClassByName(className, cc);
			}
			c.classNo = cc.no;
			
			string lecturerAccount = lecacc;
			Lecturer lec;
			if (lecRef.GetLecByID(lecturerAccount, lec)) {

			}
			else {
				lec.ID = lec.firstName = lec.lastName = lecturerAccount;
				lecRef.addLecturer(lec);
				lecRef.GetLecByID(lecturerAccount, lec);
			}
			c.lecturerNo = lec.no;

			c.startDate = stdate;
			c.endDate = eddate;
			c.dayOfWeek = dow;
			c.startHour = sthour;
			c.endHour = edhour;
			c.room = room;
			c.SemNo = semNo;

		}
		AddCourse(c);
	} while (!feof(fin));
	fclose(fin);
	return 1;
}

bool CourseList::exportFile(string fileName) {
		ofstream fout;
		fout.open(fileName);

		for (unsigned int i = 0; i < courses.size(); i++)
		{
			fout << courses[i].no << ","; //0
			fout << courses[i].ID << ","; //1
			fout << courses[i].name << ","; //2
			fout << courses[i].lecturerNo << ","; //3
			fout << courses[i].startDate << ","; //4
			fout << courses[i].endDate << ","; //5
			fout << courses[i].dayOfWeek << ","; //6
			fout << courses[i].startHour << ","; //7
			fout << courses[i].endHour << ","; //8
			fout << courses[i].room << ","; //9
			fout << courses[i].classNo << ","; //10
			fout << courses[i].SemNo << endl;
		}

		fout.close();
		return true;
	}

bool CourseList::importFromFile(string filename)
{
	ifstream fin; fin.open(filename);
	if (!fin.is_open()) return 0;

	courses.clear();

	string line, word;
	vector<string> row;

	//getline(fin, line);

	while (getline(fin, line))
	{
		row.clear();

		stringstream s(line);

		while (getline(s, word, ','))
		{
			row.push_back(word);
		}
		Course c;
		c.no = stoi(row[0]);
		c.ID = row[1];
		c.name = row[2];
		c.lecturerNo = stoi(row[3]); 
		c.startDate = row[4];
		c.endDate = row[5];
		c.dayOfWeek = row[6];
		c.startHour = row[7];
		c.endHour = row[8];
		c.room = row[9];
		c.classNo = stoi(row[10]);
		c.SemNo = stoi(row[11]);

		courses.push_back(c);
	}

	fin.close();
	return 1;
	//return false;
}

bool CourseList::getCourseOfLecturer(int LecNo, vector<Course>& list)
{
	list.clear();
	for (int i = 0; i < (int)courses.size(); i++)
	{
		if (courses[i].lecturerNo == LecNo)
		{
			list.push_back(courses[i]);
		}
	}
	return true;
}

bool CourseList::Update(int no, Course course)
{
	for (Course &i : courses)
	{
		if (i.no == no)
		{
			i.ID = course.ID;
			i.startDate = course.startDate;
			i.endDate = course.endDate;
			i.dayOfWeek = course.dayOfWeek;
			i.startHour = course.startHour;
			i.endHour = course.endHour;
			i.lecturerNo = course.lecturerNo;
			i.room = course.room;
			i.classNo = course.classNo;
			i.name = course.name;
			i.SemNo = course.SemNo;

			exportFile("course.txt");
			return true;
		}
	}
	return false;
}

bool CourseList::GetCourseById(string id, Course & course)
{
	for (auto i : courses)
	{
		if (i.ID == id)
		{
			course = i; 
			return true;
		}
	}
	return false;
}

bool CourseList::GetCourseByNo(int no, Course & course)
{
	for (auto i : courses)
	{
		if (i.no == no)
		{
			course = i;
			return true;
		}
	}
	return false;
}

int CourseList::FindNo()
{
	int index = 0;
	for (Course i : courses)
	{
		if (i.no > index) index = i.no;
	}
	return index + 1;
}

bool CourseList::Remove(int no)
{
	for (unsigned int i = 0; i < courses.size(); i++)
	{
		if (courses[i].no == no)
		{
			courses.erase(courses.begin() + i);
			exportFile("course.txt");
			return true;
		}
	}
	return false;
}

bool CourseList::GetCoursesBySemester(int SemNo, vector<Course> &list)
{
	list.clear();
	for (int i = 0; i < (int)courses.size(); i++)
	{
		if (courses[i].SemNo == SemNo)
		{
			list.push_back(courses[i]);
		}
	}
	return true;
}
