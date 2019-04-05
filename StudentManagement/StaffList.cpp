#include "StaffList.h"

int StaffList::Login(string username, string password){
	for (int i = 0; i<(int)staffs.size(); ++i) {
		if (staffs[i].ID == username && staffs[i].password == password)
			return staffs[i].no;
	}
	return -1;
}

bool StaffList::GetStafftByNo(int no, Staff &sta) {
	for (int i = 0; i<(int)staffs.size(); ++i) {
		if (staffs[i].matchNo(no)) {
			sta = staffs[i];
			return 1;
		}
	}
	return 0;
}

bool StaffList::importFromFile(string filename){
ifstream fin; fin.open(filename);
if (!fin.is_open()) return 0;

staffs.clear();

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
	Staff sta;
	sta.no = stoi(row[0]);
	sta.ID = row[1];
	sta.password = row[2];
	sta.name = row[3];
	staffs.push_back(sta);
}
fin.close();
return 1;
}

bool StaffList::exportFile(string filename) 
{
	ofstream fout;
	fout.open(filename);

	for (unsigned int i = 0; i < staffs.size(); i++)
	{
		fout << staffs[i].no << ",";
		fout << staffs[i].ID << ",";
		fout << staffs[i].password << ",";
		fout << staffs[i].name << "," << endl;
	}

	fout.close();
	return true;
}

bool StaffList::Update(int no, string newPassword)
{
	

	for (int i = 0; i < staffs.size(); i++)
	{
		if (staffs[i].matchNo(no))
		{
			staffs[i].password = newPassword;
			exportFile("staff.txt");
			return true;
		}
	}

	return false;
}
