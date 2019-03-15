#include "Screen.h"

void TextColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void startScreen()
{
	cout << "  _________    __      __    _________  " << endl;
	cout << " |   ______|  |  \\    /  |  |   ______| " << endl;
	cout << " |  |         |   \\  /   |  |  |         " << endl;
	cout << " |  |______   |    \\/    |  |  |______     " << endl;
	cout << " |______   |  |  |\\__/|  |  |______   |    " << endl;
	cout << "        |  |  |  |     |  |         |  |   " << endl;
	cout << "  ______|  |  |  |     |  |   ______|  |    " << endl;
	cout << " |_________|  |__|     |__|  |_________|    " << endl;
	cout << "____________________________________________ " << endl;
	cout << endl << " Student Management System" << endl;
	cout << " By Group [4]" << endl << endl;
	for (int i = 1; i <= 15; ++i)
	{
		cout << "/_\\";
		Sleep(160);
	}
	cout << "  Please press enter to get start!";
	cin.get();
	system("CLS");
}

int startMenu()
{
	system("CLS");
	cout << "    _______" << endl;
	cout << "   /       \\" << endl;
	cout << "1.|  Login  |" << endl;
	cout << "   \\_______/" << endl;
	cout << "    _______" << endl;
	cout << "   /       \\" << endl;
	cout << "2.|  Exit   |" << endl;
	cout << "   \\_______/" << endl;
	int x; cin >> x;
	return x;
}

int staffMenu()
{
	system("CLS");
	cout << "<<MENU>>" << endl;
	cout << "1.Class" << endl;
	cout << "2.Course" << endl;
	cout << "3.Scoreboard" << endl;
	cout << "4.Attendance list" << endl;
	int x; cin>>x;
	return x;
}

int lecturerMenu()
{
	system("cls");
	cout << "<< MENU >>" << endl;
	cout << "1.View list of course" << endl;// in current semester
	cout << "2.View list of student of a course" << endl;
	cout << "3.Attendance list" << endl;//view and edit(of a course)
	cout << "4.Scoreboard" << endl;
	int x; cin>>x;
	return x;
}

int studentMenu()
{
	system("cls");
	cout << "<<MENU>>" << endl;
	cout << "1.Check-in" << endl;
	cout << "2.View check-in result" << endl;
	cout << "3.View schedule" << endl;
	cout << "4.View score" << endl;
	int x; cin>>x;
	return x;
}

int roleSelectMenu () {
	system("cls");
	cout<<"Select your role:"<<endl;
	cout<<"1.Staff"<<endl;
	cout<<"2.Lecturer"<<endl;
	cout<<"3.Student"<<endl;
	cout<<"Enter your choice: "<<endl;
	int x; cin>>x;
	return x;
}

int staffClassMenu () {
	system("cls");
	cout<<"Staff > Class"<<endl;
	cout<<"1.Import students from CSV file"<<endl;
	cout<<"2.Add a student to a class"<<endl;
	cout<<"3.Edit a student"<<endl;
	cout<<"4.Remove a student"<<endl;
	cout<<"5.Change class of a student"<<endl;
	cout<<"6.View list of classes"<<endl;
	cout<<"7.View list of students in a class"<<endl;
	int x; cin>>x;
	return x;
}