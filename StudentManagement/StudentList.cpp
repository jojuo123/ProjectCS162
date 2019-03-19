#include "StudentList.h"

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
bool StudentList::importFromFile (string filename) {
	ifstream fin; fin.open(filename);
	if (!fin.is_open()) return 0;

	students.clear();

	string line, word;
	vector<string> row;

	getline(fin, line);

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