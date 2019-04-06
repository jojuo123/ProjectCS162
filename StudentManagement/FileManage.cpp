#include "FileManage.h"

#include <cstdio>



string eraseAllSlash(string str)
{
	string tmp = "";
	for (char c : str)
	{
		if (c != '/') tmp += c;
	}
	return tmp;
}

int importClassFile(string s)
{
	//tim class no
	ifstream fin;
	fin.open("class.txt");

	string line, word;
	vector<string> row;

	int index = 0;
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			if (line.length() == 0) break;
			row.clear();

			stringstream s(line);

			while (getline(s, word, ','))
			{
				row.push_back(word);
			}
			int tmp = stoi(row[0]);
			if (tmp > index) index = tmp;
		}
	}

	fin.close();
	index++;

	//them vao file class.txt
	ofstream fout;
	fout.open("class.txt", ios::app);

	if (fout.is_open())
	{
		fout << index << ",";
		fout << s << endl;
	}
	fout.close();
	return index;
}

bool importStudentFile(string s)
{
	//Doc file duoc import vao
	ifstream fin;
	string of("student.txt");
	fin.open(s);


	if (!fin.is_open()) return false;

	string line, word;
	vector<string> row;
	vector< vector<string>> data;

	getline(fin, line);

	while (getline(fin, line))
	{
		row.clear();

		stringstream s(line);

		while (getline(s, word, ','))
		{
			row.push_back(word);
		}

		data.push_back(row);
	}
	
	//tim student no 
	ifstream fi;
	fi.open(of);

	int index = 0;
	if (fi.is_open())
	{
		while (getline(fi, line))
		{
			if (line.length() == 0) break;
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

	//Them class vao trong file class.txt
	string a = GetFileName(s);
	stringstream str(a);
	getline(str, word, '.');
	int classNo = importClassFile(word);

	//append vao file student.txt
	index++;
	ofstream fout;
	fout.open(of, ios::app);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		fout << index++ << ",";
		fout << data[i][1] << ",";
		//tao password
		string password = eraseAllSlash(data[i][5]);
		fout << password << ",";
		fout << data[i][2] << ",";
		fout << data[i][3] << ",";
		fout << data[i][4][0] << ",";
		fout << data[i][5] << ",";
		fout << classNo << endl;
	}

	fout.close();
	fin.close();
	return true;
}
string GetFileName(const string &s)
{
	char sep = '/';
#ifdef _WIN32
	sep = '\\';
#endif
	size_t i = s.rfind(sep, s.length());
	if (i != string::npos)
		return (s.substr(i + 1, s.length()));
	return "";
}
/*
bool importCourse(string fileName, CourseList &courseList) {
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
			c.className = classstr;
			c.lecturerAccount = lecacc;
			c.startDate = stdate;
			c.endDate = eddate;
			c.dayOfWeek = dow;
			c.startHour = sthour;
			c.endHour = edhour;
			c.room = room;
		}
		courseList.AddCourse(c);
	} while (!feof(fin));
	return 1;
}
void exportCourse(string fileName, const CourseList &list) {
	ofstream fout; fout.open(fileName);
	fout << "Some nonsense header for consistency." << endl;
	for (Course c : list.courses) {
		fout << c.no << ","
			<< c.ID << ","
			<< c.name << ","
			<< c.className << ","
			<< c.lecturerAccount << ","
			<< c.startDate << ","
			<< c.endDate << ","
			<< c.dayOfWeek << ","
			<< c.startHour << ","
			<< c.endHour << ","
			<< c.room << endl;
	}
	fout.close();
}
*/