#include "LecturerList.h"

bool LecturerList::importFromFile(string filename)
{
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) return 0;

	lecturers.clear();

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
		Lecturer lec;
		lec.no = stoi(row[0]);
		lec.ID = row[1];
		lec.password = row[2];
		lec.firstName = row[3];
		lec.lastName = row[4];

		lecturers.push_back(lec);
	}
	fin.close();
	return 1;
}

int LecturerList::findId(string ID)// tim no cua new lecturer
{
	int i = (int)lecturers.size() - 1;
	return lecturers[i].no + 1;

}

int LecturerList::Login(string username, string password)
{
	for (int i = 0; i < (int)lecturers.size(); ++i)
	{
		if (lecturers[i].ID == username && lecturers[i].password == password)
			return lecturers[i].no;
	}
	return -1;
}

bool LecturerList::GetLecByNo(int no, Lecturer & lec)
{
	for (int i = 0; i < (int)lecturers.size(); ++i)
	{
		if (lecturers[i].matchNo(no))
		{
			lec = lecturers[i];
			return 1;
		}
	}
	return false;
}

bool LecturerList::GetLecByID(string ID, Lecturer & lec)
{
	for (int i = 0; i < (int)lecturers.size(); ++i)
	{
		if (lecturers[i].matchID(ID))
			lec = lecturers[i];
		return true;
	}
	return false;
}

bool LecturerList::Update(int no, string newPassword)
{
	for (int i = 0; i < (int)lecturers.size(); ++i)
	{
		if (lecturers[i].matchNo(no))
		{
			lecturers[i].password = newPassword;
			exportFile("lecturer.txt");
			return true;
		}
	}
	return false;
}

bool LecturerList::exportFile(string filename)
{
	ofstream fout;
	fout.open(filename);
	if (!fout.is_open()) return false;
	for (int i = 0; i < (int)lecturers.size(); ++i)
	{
		fout << lecturers[i].no << ',';
		fout << lecturers[i].ID << ',';
		fout << lecturers[i].password << ',';
		fout << lecturers[i].firstName << ',';
		fout << lecturers[i].lastName << endl;
	}
	return true;
}

bool LecturerList::Remove(int no)
{
	for (int i = 0; i < (int)lecturers.size(); ++i)
	{
		if (lecturers[i].matchNo(no))
		{
			lecturers.erase(lecturers.begin()+i);
			exportFile("lecturer.txt");
			return true;
		}
	}
	return false;
}

bool LecturerList::addLecturer(Lecturer &lec)
{
	Lecturer tmp;
	if (GetLecByID(lec.ID, tmp))
		return false;
	lec.no = findId(lec.ID);
	lec.password = "123456";
	lecturers.push_back(lec);
	exportFile("lecturer.txt");
	return true;
}




