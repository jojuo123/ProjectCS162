#include "Screen.h"
#include <string>

void TextColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void resizeScreen(int width, int height) {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rect;
	rect.Top = rect.Left = 0;
	rect.Bottom = height - 1;
	rect.Right = width - 1;
	COORD c = { width, height}; //col first, then row
	int tmp;

	//SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
	//tmp = SetConsoleWindowInfo(hout, TRUE, &minimal_window);
	tmp = SetConsoleScreenBufferSize(hout, c);
	tmp = SetConsoleWindowInfo(hout, true, &rect);
	tmp = SetConsoleScreenBufferSize(hout, c);
}
void getlinePassword(string &password) {
	int ch;
	do {
		ch = _getch();
		if (ch == VK_RETURN)
			return;
		else
		if (ch == VK_BACK) {
			if (!password.empty()) {
				password.pop_back();
				cout << "\b \b";
			}
			cout.flush();
		}
		else
		if (ch == 0 || ch == 0xE0) {
			ch = _getch();
		}
		else if (ch>=32) {
			password += (char)ch;
			cout << "*";
		}
	} while (1);
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
	cout << "Enter your choice: ";
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
	cout << "Enter your choice: ";
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
	cout << "Enter your choice: ";
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
	cout << "5.View profile info" << endl;
	cout << "6.Log out" << endl;
	cout << "Enter your choice: ";
	int x; cin>>x;
	return x;
}

int roleSelectMenu () {
	system("cls");
	cout<<"Select your role:"<<endl;
	cout<<"1.Staff"<<endl;
	cout<<"2.Lecturer"<<endl;
	cout<<"3.Student"<<endl;
	cout<<"Enter your choice: ";
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

bool studentLoginScreen (string &username, string &password, Global &global) {
	system("CLS");
	cout << "LOGIN" << endl;
	cout << "Username: " << endl;
	cout << "Password: " << endl;

	gotoxy(10, 1);
	cin.ignore(9999,'\n');
	getline(cin, username);

	gotoxy(10, 2);
	getlinePassword(password);
	gotoxy(0, 3);

	int res = global.stuList.Login(username, password);
	if (res == -1) return false;
	bool ret = global.stuList.GetStudentByNo(res, global.currentStudent);
	return ret;
}

void studentProfile(Global &global)
{
	Student a = global.currentStudent;
	system("cls");
	cout << "<Student>" << endl;
	cout << "ID: " << a.ID << endl;
	cout << "Name: " << a.firstName << " " << a.lastName << endl;
	cout << "Gender: " << a.gender << endl;
	cout << "Date Of Birth: " << a.DoB << endl;
	cout << "Class: " << a.classID << endl;
}