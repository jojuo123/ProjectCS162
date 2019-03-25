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
	password = "";
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

int studentMenu(string firstName, string lastName)
{
	system("cls");
	cout << "Welcome, " << firstName << " " << lastName << endl;
	cout << "1.Check-in" << endl;
	cout << "2.View check-in result" << endl;
	cout << "3.View schedule" << endl;
	cout << "4.View score" << endl;
	cout << "5.View profile info" << endl;
	cout << "6.Change password" << endl;
	cout << "7.Log out" << endl;
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
	cout << "4.Exit" << endl;
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

bool studentLoginScreen (Global &global) {
	system("CLS");
	cout << "STUDENT LOGIN" << endl;
	cout << "Username: " << endl;
	cout << "Password: " << endl;

	gotoxy(10, 1);
	cin.ignore(9999,'\n');
	getline(cin, global.username);

	gotoxy(10, 2);
	getlinePassword(global.password);
	gotoxy(0, 3);

	int res = global.stuList.Login(global.username, global.password);
	if (res == -1) return false;
	global.currentlyLoggedIn = global.stuList.GetStudentByNo(res, global.currentStudent);
	if (global.currentlyLoggedIn)
		global.currentRole = 3; // ROLE_STUDENT
	return global.currentlyLoggedIn;
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
	_getch();
}
bool lecturerLoginScreen(Global &global) {
	system("CLS");
	cout << "LECTURER LOGIN" << endl;
	cout << "Username: " << endl;
	cout << "Password: " << endl;

	gotoxy(10, 1);
	cin.ignore(9999, '\n');
	getline(cin, global.username);

	gotoxy(10, 2);
	getlinePassword(global. password);
	gotoxy(0, 3);

	int res = global.lecList.Login(global.username, global.password);
	if (res == -1) return false;
	global.currentlyLoggedIn = global.lecList.GetLecByNo(res, global.currentLecturer);
	
	if (global.currentlyLoggedIn)
		global.currentRole = 2; // ROLE_LECTURER
	return global.currentlyLoggedIn;
}
bool staffLoginScreen(Global &global){
	system("CLS");
	cout << "STAFF LOGIN" << endl;
	cout << "Username: " << endl;
	cout << "Password: " << endl;

	gotoxy(10, 1);
	cin.ignore(9999, '\n');
	getline(cin, global.username);

	gotoxy(10, 2);
	getlinePassword(global.password);
	gotoxy(0, 3);

	int res = global.staffList.Login(global.username, global.password);
	if (res == -1) return false;

	global.currentlyLoggedIn = global.staffList.GetStafftByNo(res, global.currentStaff);
	if (global.currentlyLoggedIn)
		global.currentRole = 1; // ROLE_STAFF
	return global.currentlyLoggedIn;
}

bool studentChangePasswordScreen(Global &global) {
	system("CLS");
	cout << "CHANGE PASSWORD" << endl;
	cout << "Enter current password: " << endl;
	gotoxy(24, 1);
	string oldPassword, newPassword, newPasswordReenter;
	getlinePassword(oldPassword);
	gotoxy(0, 2);

	if (oldPassword == global.password) {
		cout << "Enter new password: " << endl;
		cout << "Enter new password again: " << endl;
		gotoxy(20, 2);
		getlinePassword(newPassword);
		gotoxy(26, 3);
		getlinePassword(newPasswordReenter);
		gotoxy(0, 4);
		if (newPassword == newPasswordReenter) {
			global.password = newPassword;
			global.currentStudent.password = newPassword;
			global.stuList.Update(global.currentStudent.no, newPassword);
			cout << "Password change complete." << endl;
			cout << "Press any key to return.";
			_getch();
			return 1;
		}
		else {
			cout << "Re-enter password doesn't match. Revert to old password." << endl;
			cout << "Press any key to return.";
			_getch();
			return 0;
		}
	}
	else {
		cout << "Wrong password. Any key to return..." << endl;
		_getch();
		return 0;
	}
}

bool lecturerChangePasswordScreen(Global &global){
	system("CLS");
	cout << "CHANGE PASSWORD" << endl;
	cout << "Enter current password: " << endl;
	gotoxy(24, 1);
	string oldPassword, newPassword, newPasswordReenter;
	getlinePassword(oldPassword);
	gotoxy(0, 2);

	if (oldPassword == global.password) {
		cout << "Enter new password: " << endl;
		cout << "Enter new password again: " << endl;
		gotoxy(20, 2);
		getlinePassword(newPassword);
		gotoxy(26, 3);
		getlinePassword(newPasswordReenter);
		gotoxy(0, 4);
		if (newPassword == newPasswordReenter) {
			global.password = newPassword;
			global.currentLecturer.password = newPassword;
			global.lecList.Update(global.currentLecturer.no, newPassword);
			cout << "Password change complete." << endl;
			cout << "Press any key to return.";
			_getch();
			return 1;
		}
		else {
			cout << "Re-enter password doesn't match. Revert to old password." << endl;
			cout << "Press any key to return.";
			_getch();
			return 0;
		}
	}
	else {
		cout << "Wrong password. Any key to return..." << endl;
		_getch();
		return 0;
	}
}

bool staffChangePasswordScreen(Global &global){
	system("CLS");
	cout << "CHANGE PASSWORD" << endl;
	cout << "Enter current password: " << endl;
	gotoxy(24, 1);
	string oldPassword, newPassword, newPasswordReenter;
	getlinePassword(oldPassword);
	gotoxy(0, 2);
	if (oldPassword == global.password) {
		cout << "Enter new password: " << endl;
		cout << "Enter new password again: " << endl;
		gotoxy(20, 2);
		getlinePassword(newPassword);
		gotoxy(26, 3);
		getlinePassword(newPasswordReenter);
		gotoxy(0, 4);
		if (newPassword == newPasswordReenter) {
			global.password = newPassword;
			global.currentStaff.password = newPassword;
			global.staffList.Update(global.currentStaff.no, newPassword);
			cout << "Password change complete." << endl;
			cout << "Press any key to return.";
			_getch();
			return 1;
		}
		else {
			cout << "Re-enter password doesn't match. Revert to old password." << endl;
			cout << "Press any key to return.";
			_getch();
			return 0;
		}
	}
	else {
		cout << "Wrong password. Any key to return..." << endl;
		_getch();
		return 0;
	}
}

int staffMenu(string name) {
	system("cls");
	cout << "Welcome, " << name << endl;
	cout << "1. Change password" << endl;
	cout << "2. Edit an existing student" << endl;
	cout << "3. Remove a student" << endl;
	cout << "4. Log out" << endl;
	cout << "Enter your choice: ";
	int x; cin >> x;
	return x;
}
int lecturerMenu(string firstName, string lastName){
	system("cls");
	cout << "Welcome, " << firstName << " " << lastName << endl;
	cout << "1.View list of courses in current semester" << endl;
	cout << "2.View list of students of a course" << endl;
	cout << "3.Attendance list of a course" << endl;
	cout << "4.Edit an attendance" << endl;
	cout << "5.Import scoreboard from CSV" << endl;
	cout << "6.View scoreboard" << endl;
	cout << "7.Edit grade of a student" << endl;
	cout << "8.Change password" << endl;
	cout << "9.Log out" << endl;
	cout << "Enter your choice: ";
	int x; cin >> x;
	return x;
}

void logout(Global &global) {
	if (global.currentlyLoggedIn) {
		global.username = global.password = "";
		global.currentStaff = Staff();
		global.currentLecturer = Lecturer();
		global.currentStudent = Student();
		global.currentRole = 0;
		global.currentlyLoggedIn = false;
	}
}

void removeStudentScreen(Global &global) {
	system("CLS");
	cout << "Student deletetion wizard" << endl;
	string id;
	cout << "Enter student ID: ";
	cin.ignore(9999, '\n');
	getline(cin, id);

	Student stu;
	if (global.stuList.GetStudentByID(id, stu) == 0) {
		cout << "There is no such student ID." << endl;
		cout << "Any key to return." << endl;
		_getch();
	}
	else {
		cout << id<<"'s profile" << endl;
		cout << "ID: " << stu.ID << endl;
		cout << "Name: " << stu.firstName << " " << stu.lastName << endl;
		cout << "Gender: " << stu.gender << endl;
		cout << "Date Of Birth: " << stu.DoB << endl;
		cout << "Class: " << stu.classID << endl;
		cout << endl;
		cout << "Are you sure you want to delete this student? [Y/N]: ";

		string tmp = "N";
		getline(cin, tmp);
		if (tmp[0] == 'Y' || tmp[0] == 'y') {
			global.stuList.Remove(stu.no);
			cout << "Removal complete. Any key to return..." << endl;
			_getch();
		}
	}
}
bool getlineESC(string &str) { //Return 1 if ESC during typing, 0 if not.
	int ch;
	str = "";
	do {
		ch = _getch();
		if (ch == VK_RETURN)
			return 0;
		else
		if (ch == VK_BACK) {
			if (!str.empty()) {
				str.pop_back();
				cout << "\b \b";
			}
			cout.flush();
		}
		else if (ch == VK_ESCAPE) {
			return 1;
		}
		else
		if (ch == 0 || ch == 0xE0) {
			ch = _getch();
		}
		else if (ch >= 32) {
			str += (char)ch;
			cout << str.back();
			cout.flush();
		}
	} while (1);
}
bool isLeapYear(int year)
{
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 == 0)
		return true;
	else
		return false;
}
bool isValidDoB(string dob) {
	int d, m, y;
	if (sscanf(dob.c_str(), "%d/%d/%d", &d, &m, &y) != 3) return 0;
	if (m == 4 || m == 6 || m == 9 || m == 11)
		return (d >= 1 && d <= 30);
	else if (m == 2) {
		int numDay = isLeapYear(y) ? 29 : 28;
		return (d >= 1 && d <= numDay);
	}
	else return (d >= 1 && d <= 31);
}

void editStudentScreen(Global &global) {
	system("CLS");
	cout << "Student editing wizard" << endl;
	cout << "Press ESC at any point to discard changes and return." << endl;
	string id;
	cout << "Enter student ID: "; 
	cin.ignore(9999,'\n');
	getline(cin, id);

	Student stu;
	if (global.stuList.GetStudentByID(id, stu) == 0) {
		cout << "There is no such student ID." << endl;
		cout << "Any key to return." << endl;
		_getch();
	}
	else {
		cout << id << "'s OLD profile" << endl;
		cout << "ID: " << stu.ID << endl;
		cout << "Name: " << stu.firstName << " " << stu.lastName << endl;
		cout << "Gender: " << stu.gender << endl;
		cout << "Date Of Birth: " << stu.DoB << endl;

		//WAIT FOR ClassList.h implementation
		cout << "Class: " << stu.classID << endl;
		cout << endl;

		int newProfX = 30;
		gotoxy(newProfX, 3); cout << "NEW PROFILE";
		gotoxy(newProfX, 4); cout << "ID: " << stu.ID;
		gotoxy(newProfX, 5); cout << "First Name: ";
		gotoxy(newProfX, 6); cout << "Last Name: ";
		gotoxy(newProfX, 7); cout << "Gender (M/F): ";
		gotoxy(newProfX, 8); cout << "DoB (dd/mm/yyyy): ";
		gotoxy(newProfX, 9); cout << "Class: ";

		string newID, newFirstName, newLastName, newGender, newDoB, newClass;
		gotoxy(newProfX + 13, 5); if (getlineESC(newFirstName)) return;
		gotoxy(newProfX + 12, 6); if (getlineESC(newLastName)) return;
		do {

			gotoxy(newProfX + 15, 7); if (getlineESC(newGender)) return;
		} while (newGender[0] != 'M' && newGender[0] != 'm'&&newGender[0] != 'F'&&newGender[0] != 'f');
		if (newGender[0] == 'm') newGender[0] = 'M';
		if (newGender[0] == 'f') newGender[0] = 'F';

		do {
			gotoxy(newProfX + 19, 8); if (getlineESC(newDoB)) return;
		} while (!isValidDoB(newDoB));
		
		//WAIT FOR ClassList.h IMPLEMENTATION
		//For now just enter classNo a.k.a classID
		/*do {
			gotoxy(newProfX + 4, 4); if (getlineESC(newClass)) return;
		} while (!isValidClass(newClass)); */
		string newClassNoStr; int newClassNo;
		gotoxy(newProfX + 8, 9); if (getlineESC(newClassNoStr)) return;
		newClassNo = stoi(newClassNoStr);

		gotoxy(newProfX, 10); string tmp;
		cout << "Is that ok? [y/n]: "; if (getlineESC(tmp)) return;
		if (tmp[0] == 'y' || tmp[0] == 'Y') {
			//UPDATE CODE GOES HERE. WILL BE CHANGED WHEN BACK-END CHANGES
			global.stuList.Remove(stu.no);

			stu.firstName = newFirstName;
			stu.lastName = newLastName;
			stu.gender = newGender[0];
			stu.DoB = newDoB;
			stu.classID = newClassNo;
			global.stuList.AddStudent(stu);
		}
	}
}
int mainMenuScreen(Global &global) {
	bool running = true;
	while (running) {
		int currentRole = -1;
		while (currentRole<0 || currentRole>4)
			currentRole = roleSelectMenu();
		switch (currentRole) {
		case 1: {
					bool loginStatus = staffLoginScreen(global);
					if (!loginStatus) {
						cout << "Login failed!. Any key to return...";
						_getch();
						break;
					}
					else {
						while (global.currentlyLoggedIn) {
							int choice = staffMenu(global.currentStaff.name);
							switch (choice)
							{
								/*
	cout << "1. Change password" << endl;
	cout << "2. Edit an existing student" << endl;
	cout << "3. Remove a student" << endl;
	cout << "4. Log out" << endl;
								*/
							case 1: staffChangePasswordScreen(global); break;
							case 2: editStudentScreen(global); break;
							case 3: removeStudentScreen(global); break;
							case 4: logout(global); break;
							default:
								break;
							}
						}

					}
		}; break;
		case 2: {
					bool loginStatus = lecturerLoginScreen(global);
					if (!loginStatus) {
						cout << "Login failed!. Any key to return...";
						_getch();
						break;
					}
					else {
						while (global.currentlyLoggedIn) {
							int choice = lecturerMenu(global.currentLecturer.firstName, global.currentLecturer.lastName);
							switch (choice)
							{
								/*
								cout << "1.View list of courses in current semester" << endl;
								cout << "2.View list of students of a course" << endl;
								cout << "3.Attendance list of a course" << endl;
								cout << "4.Edit an attendance" << endl;
								cout << "5.Import scoreboard from CSV" << endl;
								cout << "6.View scoreboard" << endl;
								cout << "7.Edit grade of a student" << endl;
								cout << "8.Change password" << endl;
								cout << "9.Log out" << endl;
								*/
							case 1: break;
							case 2: break;
							case 3: break;
							case 4: break;
							case 5: break;
							case 6: break;
							case 7: break;
							case 8: lecturerChangePasswordScreen(global); break;
							case 9: logout(global); break;
							default:
								break;
							}
						}

					}

		}; break;
		case 3: {
					bool loginStatus = studentLoginScreen(global);
					if (!loginStatus) {
						cout << "Login failed!. Any key to return...";
						_getch();
						break;
					}
					else {
						while (global.currentlyLoggedIn) {
							int choice = studentMenu(global.currentStudent.firstName, global.currentStudent.lastName);
							switch (choice)
							{
								/*
									cout << "1.Check-in" << endl;
									cout << "2.View check-in result" << endl;
									cout << "3.View schedule" << endl;
									cout << "4.View score" << endl;
									cout << "5.View profile info" << endl;
									cout << "6.Change password" << endl;
									cout << "7.Log out" << endl;
								*/
							case 1: break;
							case 2: break; 
							case 3: break;
							case 4: break;
							case 5: studentProfile(global); break;
							case 6: studentChangePasswordScreen(global); break;
							case 7: logout(global); break;
							default:
								break;
							}
						}
					}

		}; break;
		case 4: running = false; break;
		}
	}
	return 0;
}