#include "CourseStudentList.h"

bool CourseStudentList::AddStudentToCourse(int noCourse, int noStudent, CourseList &cList, StudentList &stuList)
{
	CourseStudent cs(noCourse, noStudent);
	bool res = true;
	//check if the student or course is existed
	Course c;
	Student s;
	if (cList.GetCourseByNo(noCourse, c) && stuList.GetStudentByNo(noStudent, s))
	{
		//check if that student is in the class which is assigned to that course
		if (c.classNo == s.classID)
		{
			res = false;
		}
		else
		{
			//check if that student has enrolled personally in that course
			for (auto i : courseStudents)
			{
				if (i.Match(noCourse, noStudent))
				{
					res = false;
					break;
				}
			}
			if (res)
				courseStudents.push_back(cs);
		}
	}
	else
	{
		res = false;
	}
	
	SaveToFile("coursestudent.txt");

	return res;
}

bool CourseStudentList::GetStudentOfCourse(int noCourse, vector<Student>& list, StudentList &stuList, CourseList &cList)
{
	list.clear();
	//get from class of course
	Course c;
	if (cList.GetCourseByNo(noCourse, c))
	{
		int ClassNo = c.classNo;
		stuList.GetStudentsFromClass(ClassNo, list);
	}
	//get from coursestudent
	for (auto i : courseStudents)
	{
		if (i.CourseNo == noCourse)
		{
			Student stu;
			if (stuList.GetStudentByNo(i.StudentNo, stu))
			{
				list.push_back(stu);
			}
		}
	}

	return true;
}

bool CourseStudentList::GetCoursesOfStudent(int noStudent, vector<Course>& list, CourseList &cList, StudentList &stuList)
{
	list.clear();
	//get by class
	Student stu;
	if (stuList.GetStudentByNo(noStudent, stu))
	{
		int classNo = stu.classID;
		for (auto i : cList.courses)
		{
			if (i.classNo == classNo)
			{
				list.push_back(i);
			}
		}
	}
	//get by student
	for (auto i : courseStudents)
	{
		if (i.StudentNo == noStudent)
		{
			Course c;
			if (cList.GetCourseByNo(i.CourseNo, c))
			{
				list.push_back(c);
			}
		}
	}
	return true;
}

bool CourseStudentList::Remove(int noCourse, int noStudent)
{
	for (int i = 0; i < (int)courseStudents.size(); i++)
	{
		if (courseStudents[i].Match(noCourse, noStudent))
		{
			courseStudents.erase(courseStudents.begin() + i);
			SaveToFile("coursestudent.txt");
			return true;
		}
	}
	return false;
}

bool CourseStudentList::SaveToFile(string filename)
{
	ofstream fout;
	fout.open(filename);

	for (auto i : courseStudents)
	{
		fout << i.CourseNo << ",";
		fout << i.StudentNo << endl;
	}

	fout.close();
	return true;
}

bool CourseStudentList::ImportFromFile(string filename)
{
	ifstream fin; fin.open(filename);
	if (!fin.is_open()) return 0;

	courseStudents.clear();

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
		CourseStudent cs;
		cs.CourseNo = stoi(row[0]);
		cs.StudentNo = stoi(row[1]);
		
		courseStudents.push_back(cs);
	}

	fin.close();
	return 1;
}
