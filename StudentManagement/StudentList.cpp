#include "StudentList.h"

string StudentList::eraseAllSlash(string str)
{
	string tmp = "";
	for (char c : str)
	{
		if (c != '/') tmp += c;
	}
	return tmp;
}

int StudentList::Login(string username, string password) {
	for (int i=0; i<(int)students.size(); ++i) {
		if (students[i].ID == username && students[i].password == password)
			return students[i].no;
	}
	return -1;
}

bool StudentList::GetStudentByNo (int no, Student &stu) {
	for (int i=0; i<(int)students.size(); ++i) {
		if (students[i].matchNo(no)) {
			stu = students[i];
			return 1;
		}
	}
	return 0;
}
bool StudentList::GetStudentByID(string ID, Student & stu)
{
	for (int i = 0; i < (int)students.size(); ++i) {
		if (students[i].MatchId(ID)) {
			stu = students[i];
			return 1;
		}
	}
	return 0;
}
int StudentList::findId()
{
	ifstream fi;
	fi.open("student.txt");

	string word, line;
	vector<string> row;

	int index = 0;
	if (fi.is_open())
	{
		while (getline(fi, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
			{
				row.push_back(word);
			}
			int tmp = stoi(row[0]);
			if (tmp > index) index = tmp;
		}
	}
	fi.close();

	return index + 1;
}
bool StudentList::importFromFile (string filename) {
	ifstream fin; fin.open(filename);
	if (!fin.is_open()) return 0;

	students.clear();

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
		Student stu;
		stu.no = stoi(row[0]);
		stu.ID = row[1];
		stu.password = row[2];
		stu.firstName = row[3];
		stu.lastName = row[4];
		stu.gender = row[5][0];
		stu.DoB = row[6];
		stu.classID = stoi(row[7]);

		students.push_back(stu);
	}

	return 1;
}

bool StudentList::exportFile(string filename) //ham nay la rewrite file
{
	ofstream fout;
	fout.open(filename);

	for (unsigned int i = 0; i < students.size(); i++)
	{
		fout << students[i].no << ",";
		fout << students[i].ID << ",";
		fout << students[i].password << ",";
		fout << students[i].firstName << ",";
		fout << students[i].lastName << ",";
		fout << students[i].gender << ",";
		fout << students[i].DoB << ",";
		fout << students[i].classID << endl;
	}

	fout.close();
	return true;
}

bool StudentList::AddStudent(Student stu)
{
	Student tmp;
	if (GetStudentByID(stu.ID, tmp)) return false;

	// tao no va password
	stu.no = findId();
	stu.password = eraseAllSlash(stu.DoB);

	//them vao vector
	students.push_back(stu);

	//sua trong file
	exportFile("student.txt");

	return false;
}
bool StudentList::Update(int no, string newPassword)
{
	//Student tmp;
	
	for (int i = 0; i < (int)students.size(); i++)
	{
		if (students[i].matchNo(no))
		{
			students[i].password = newPassword;
			exportFile("student.txt");
			return true;
		}
	}

	return false;
}
bool StudentList::Remove(int no)
{
	for (int i = 0; i < (int)students.size(); i++)
	{
		if (students[i].matchNo(no))
		{
			students.erase(students.begin() + i);
			exportFile("student.txt");
			return true;
		}
	}
	return false;
}

bool StudentList::UpdateInfo(int no, Student student)
{
	for (int i = 0; i < (int)students.size(); ++i)
	{
		if (students[i].matchNo(no))
		{
			students[i].firstName = student.firstName;
			students[i].lastName = student.lastName;
			students[i].DoB = student.DoB;
			students[i].gender = student.gender;
			exportFile("student.txt");
			return true;
		}
	}
	return false;
}

bool StudentList::GetStudentsFromClass(int classNo, vector<Student>& list)
{
	list.clear();
	for (int i = 0; i < (int)students.size(); ++i)
	{
		if (students[i].classID == classNo)
			list.push_back(students[i]);
	}
	return true;
}

bool StudentList::ChangeClass(int no, int newClassNo)
{
	for (int i = 0; i < (int)students.size(); ++i)
	{
		if (students[i].matchNo(no))
		{
			students[i].classID = newClassNo;
			exportFile("student.txt");
			return true;
		}
	}
	return false;
}
