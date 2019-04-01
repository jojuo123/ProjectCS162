#include"ClassList.h"
using namespace std;

bool ClassList::getClassByNo(int no, Class&cla)
{
	for (int i = 0; i<(int)classes.size(); ++i) {
		if (classes[i].matchNo(no)) {
			cla = classes[i];
			return 1;
		}
	}
	return 0;
}

bool ClassList::getClassByName(string name, Class&cla)
{
	for (int i = 0; i<(int)classes.size(); ++i) {
		if (classes[i].matchClass(name)) {
			cla = classes[i];
			return 1;
		}
	}
	return 0;
}

bool ClassList::importFromFile(string filename)
{
	ifstream fin; fin.open(filename);
	if (!fin.is_open()) return 0;

	classes.clear();

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
		Class cla;
		cla.no = stoi(row[0]);
		cla.name = row[1];

		classes.push_back(cla);
	}

	return 1;
}

bool ClassList::exportFile(string filename)
{
	ofstream fout;
	fout.open(filename);

	for (unsigned int i = 0; i < classes.size(); i++)
	{
		fout << classes[i].no << ",";
		fout << classes[i].name << endl;
	}

	fout.close();
	return true;
}

bool ClassList::addClass(Class cla)
{	
	Class tmp;
	if (getClassByName(cla.name,tmp)) return false;
	for (int i = 0; i < (int)classes.size(); ++i)
		cla.no = classes[i].no + 1;
	if (cla.no <= 0)
		cla.no = 1;
	//them vao vector
	classes.push_back(cla);

	//sua trong file
	exportFile("class.txt");

	return true;
	
}

bool ClassList::remove(int no)
{
	for (int i = 0; i < classes.size(); i++)
	{
		if (classes[i].matchNo(no))
		{
			classes.erase(classes.begin() + i);
			exportFile("class.txt");
			return true;
		}
	}
	return false;
}



