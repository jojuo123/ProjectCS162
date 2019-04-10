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
int WhereY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}
int WhereX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
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
		if (ch == 0 || ch == 0xE0) ch = _getch();
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
		else if (ch>=32 || ch<=127) {
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
	cout << "  Please any key to get start!";
	_getch();
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

int studentMenu(string firstName, string lastName)
{
	system("cls");
	cout << "Welcome, " << firstName << " " << lastName << endl;
	cout << "1.Check-in" << endl;
	cout << "2.View attendance" << endl;
	cout << "3.View schedule" << endl;
	cout << "4.View scoreboard" << endl;
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

//OLD MENU
/*
int staffMenu(string name) {
	system("cls");
	cout << "Welcome, " << name << endl;
	cout << "1. Change password" << endl;
	cout << "2. Import student from <ClassName>.csv" << endl;
	cout << "3. Add (manually) a new student" << endl;
	cout << "4. Edit student profile" << endl;
	cout << "5. Change class of a student" << endl;
	cout << "6. Remove a student" << endl;
	cout << "7. List all classes" << endl;
	cout << "8. List all student in a class" << endl;

	cout << "9. Create an academic year" << endl;
	cout << "10. Delete an academic year" << endl;
	cout << "11. View academic years" << endl;
	cout << "12. Create a semester" << endl;
	cout << "13. Delete a semester" << endl;
	cout << "14. View all semesters" << endl;
	cout << "15. Import Courses.CSV into semester" << endl;
	cout << "16. Add (manually) new course" << endl;
	cout << "17. Edit a course" << endl;
	cout << "18. Remove a course" << endl;

	cout << "19. UnEnroll a student from a course" << endl;
	cout << "20. Enroll a student to a course" << endl;
	cout << "21. View all courses in a semester" << endl;
	cout << "22. View who enrolled in a course" << endl;
	cout << "23. Create a lecturer account" << endl;
	cout << "24. View all lecturers" << endl;
	cout << "25. View attendance list of a course" << endl;
	cout << "26. View scoreboard of a course" << endl;
	cout << "27. Log out" << endl;
	cout << "Enter your choice: ";
	int x; cin >> x;
	return x;
} 
*/
int staffMenu(string name) {
	system("cls");
	cout << "Welcome, " << name << endl;
	int x_classStudent = 0, y_classStudent = 1;
	cout << "CLASS & STUDENT [1-9]" << endl;
	gotoxy(x_classStudent, y_classStudent + 1);
	cout << "1. Import student from <ClassName>.csv" << endl;
	gotoxy(x_classStudent, y_classStudent + 2);
	cout << "2. Add (manually) a new student" << endl;
	gotoxy(x_classStudent, y_classStudent + 3);
	cout << "3. Edit student profile" << endl;
	gotoxy(x_classStudent, y_classStudent + 4);
	cout << "4. Change class of a student" << endl;
	gotoxy(x_classStudent, y_classStudent + 5);
	cout << "5. Remove a student" << endl;
	gotoxy(x_classStudent, y_classStudent + 6);
	cout << "6. View all classes" << endl;
	gotoxy(x_classStudent, y_classStudent + 7);
	cout << "7. View all student in a class" << endl;
	gotoxy(x_classStudent, y_classStudent + 8);
	cout << "8. UnEnroll a student from a course" << endl;
	gotoxy(x_classStudent, y_classStudent + 9);
	cout << "9. Enroll a student to a course" << endl;

	int x_yearSem = 50, y_yearSem = 1;
	gotoxy(x_yearSem, y_yearSem);
	cout << "ACADEMIC YEAR & SEMESTER [10-15]" << endl;
	gotoxy(x_yearSem, y_yearSem + 1);
	cout << "10. Create an academic year" << endl;
	gotoxy(x_yearSem, y_yearSem + 2);
	cout << "11. Delete an academic year" << endl;
	gotoxy(x_yearSem, y_yearSem + 3);
	cout << "12. View academic years" << endl;
	gotoxy(x_yearSem, y_yearSem + 4);
	cout << "13. Create a semester" << endl;
	gotoxy(x_yearSem, y_yearSem + 5);
	cout << "14. Delete a semester" << endl;
	gotoxy(x_yearSem, y_yearSem + 6);
	cout << "15. View all semesters" << endl;

	int x_course = 0, y_course = 14;
	gotoxy(x_course, y_course);
	cout << "COURSE [16-21]" << endl;
	gotoxy(x_course, y_course + 1);
	cout << "16. Import Courses.CSV into semester" << endl;
	gotoxy(x_course, y_course + 2);
	cout << "17. Add (manually) new course" << endl;
	gotoxy(x_course, y_course + 3);
	cout << "18. Edit a course" << endl;
	gotoxy(x_course, y_course + 4);
	cout << "19. Remove a course" << endl;
	gotoxy(x_course, y_course + 5);
	cout << "20. View all courses in a semester" << endl;
	gotoxy(x_course, y_course + 6);
	cout << "21. View who enrolled in a course" << endl;

	int x_lec = 50, y_lec = 9;
	gotoxy(x_lec, y_lec);
	cout << "LECTURER [22-23]" << endl;
	gotoxy(x_lec, y_lec+1);
	cout << "22. Create a lecturer account" << endl;
	gotoxy(x_lec, y_lec+2);
	cout << "23. View all lecturers" << endl;

	int x_attScore = 50, y_attScore = 14;
	gotoxy(x_attScore, y_attScore);
	cout << "ATTENDANCE & SCOREBOARD [24-25]" << endl;
	gotoxy(x_attScore, y_attScore+1);
	cout << "24. View attendance list of a course" << endl;
	gotoxy(x_attScore, y_attScore+2);
	cout << "25. View scoreboard of a course" << endl;

	int x_acc = 50, y_acc = 18;
	gotoxy(x_acc, y_acc);
	cout << "ACCOUNT SETTINGS [26-27]" << endl;
	gotoxy(x_acc, y_acc+1);
	cout << "26. Change password" << endl;
	gotoxy(x_acc, y_acc+2);
	cout << "27. Log out" << endl;

	int x_choice = 0, y_choice = 22;
	gotoxy(x_choice, y_choice);
	cout << "Enter your choice: ";
	int x; cin >> x;
	return x;
}

int lecturerMenu(string firstName, string lastName){
	system("cls");
	cout << "Welcome, " << firstName << " " << lastName << endl;
	cout << "1. View list of courses" << endl;
	cout << "2. View students enrolled in a course" << endl;
	cout << "3. View attendance list of a course" << endl;
	cout << "4. Edit an attendance" << endl;
	cout << "5. Import scoreboard from CSV" << endl;
	cout << "6. View scoreboard" << endl;
	cout << "7. Edit score of a student" << endl;
	cout << "8. Change password" << endl;
	cout << "9. Log out" << endl;
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

void studentRemoveScreen(Global &global) {
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
		if (ch == VK_RETURN) {
			cout << "\n";
			return 0;
		}
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

void studentEditScreen(Global &global) {
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

		Class cla;
		if (!global.classList.getClassByNo(stu.classID, cla)) {
			cout << "DATABASE FAULT!!!" << endl;
			_getch();
			return;
		}
		cout << "Class: " << cla.name << endl;
		cout << endl;

		int newProfX = 30;
		gotoxy(newProfX, 3); cout << "NEW PROFILE";
		gotoxy(newProfX, 4); cout << "ID: " << stu.ID;
		gotoxy(newProfX, 5); cout << "First Name: ";
		gotoxy(newProfX, 6); cout << "Last Name: ";
		gotoxy(newProfX, 7); cout << "Gender (M/F): ";
		gotoxy(newProfX, 8); cout << "DoB (dd/mm/yyyy): ";
		gotoxy(newProfX, 9); cout << "Class: " << cla.name;

		string newID, newFirstName, newLastName, newGender, newDoB, newClass;
		gotoxy(newProfX + 12, 5); if (getlineESC(newFirstName)) return;
		gotoxy(newProfX + 11, 6); if (getlineESC(newLastName)) return;
		do {
			gotoxy(newProfX + 14, 7);  cout << "              ";
			gotoxy(newProfX + 14, 7);
			if (getlineESC(newGender)) return;
		} while (newGender[0] != 'M' && newGender[0] != 'm'&&newGender[0] != 'F'&&newGender[0] != 'f');
		if (newGender[0] == 'm') newGender[0] = 'M';
		if (newGender[0] == 'f') newGender[0] = 'F';

		do {
			gotoxy(newProfX + 18, 8);  cout << "              ";
			gotoxy(newProfX + 18, 8);
			if (getlineESC(newDoB)) return;
		} while (!isValidDoB(newDoB));
		
		//WAIT FOR ClassList.h IMPLEMENTATION
		//For now just enter classNo a.k.a classID
		/*do {
			gotoxy(newProfX + 4, 4); if (getlineESC(newClass)) return;
		} while (!isValidClass(newClass)); */

		gotoxy(newProfX, 11); string tmp;
		cout << "Is that ok? [y/n]: "; if (getlineESC(tmp)) return;
		if (tmp[0] == 'y' || tmp[0] == 'Y') {
			stu.firstName = newFirstName;
			stu.lastName = newLastName;
			stu.gender = newGender[0];
			stu.DoB = newDoB;
			global.stuList.UpdateInfo(stu.no, stu);

			cout << "Update info complete." << endl;
			_getch();
		}
		else {
			cout << "Discard all changes. Any key to return." << endl;
			_getch();
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
	cout << "1. Import student from <ClassName>.csv" << endl;
	cout << "2. Add (manually) a new student" << endl;
	cout << "3. Edit student profile" << endl;
	cout << "4. Change class of a student" << endl;
	cout << "5. Remove a student" << endl;
	cout << "6. View all classes" << endl;
	cout << "7. View all student in a class" << endl;
	cout << "8. UnEnroll a student from a course" << endl;
	cout << "9. Enroll a student to a course" << endl;

	cout << "10. Create an academic year" << endl;
	cout << "11. Delete an academic year" << endl;
	cout << "12. View academic years" << endl;
	cout << "13. Create a semester" << endl;
	cout << "14. Delete a semester" << endl;
	cout << "15. View all semesters" << endl;

	cout << "16. Import Courses.CSV into semester" << endl;
	cout << "17. Add (manually) new course" << endl;
	cout << "18. Edit a course" << endl;
	cout << "19. Remove a course" << endl;
	cout << "20. View all courses in a semester" << endl;
	cout << "21. View who enrolled in a course" << endl;

	cout << "22. Create a lecturer account" << endl;
	cout << "23. View all lecturers" << endl;
	cout << "24. View attendance list of a course" << endl;
	cout << "25. View scoreboard of a course" << endl;

	cout << "26. Change password" << endl;
	cout << "27. Log out" << endl;
								*/

							case 1: studentImportFromCSVScreen(global); break;
							case 2: studentAddScreen(global); break;
							case 3: studentEditScreen(global); break;
							case 4: studentChangeClassScreen(global); break;
							case 5: studentRemoveScreen(global); break;
							case 6: classListScreen(global); break;
							case 7: classStudentListScreen(global); break;
							case 8: courseStudentRemoveScreen(global); break;
							case 9: courseStudentAddScreen(global); break;

							case 10: academicYearCreateScreen(global); break;
							case 11: academicYearDeleteScreen(global); break;
							case 12: {
										 system("CLS");
										 cout << "ACADEMIC YEAR VIEW" << endl;
										 academicYearScreenUtil(global, 0);
										 _getch();
										 break;
							}
							case 13: semesterCreateScreen(global); break;
							case 14: semesterDeleteScreen(global); break;
							case 15: semesterListScreen(global); break;

							case 16: courseImportFromCSVScreen(global); break;
							case 17: courseAddScreen(global); break;
							case 18: courseEditScreen(global); break;
							case 19: courseRemoveScreen(global); break;
							case 20: semesterListAllCourseScreen_staff(global); break;
							case 21: courseListAllStudentScreen(global); break;

							case 22: lecturerAddScreen(global); break;
							case 23: lecturerListScreen(global); break;
							case 24: courseViewAttendanceListScreen_staff(global); break;
							case 25: courseViewScoreboardScreen_staff(global); break;

							case 26: staffChangePasswordScreen(global); break;
							case 27: logout(global); break;
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

	
	cout << "1. View list of courses" << endl;
	cout << "2. View students enrolled in a course" << endl;
	cout << "3. View attendance list of a course" << endl;
	cout << "4. Edit an attendance" << endl;
	cout << "5. Import scoreboard from CSV" << endl;
	cout << "6. View scoreboard" << endl;
	cout << "7. Edit score of a student" << endl;
	cout << "8. Change password" << endl;
	cout << "9. Log out" << endl;
								*/
							case 1: semesterListAllCourseScreen_lecturer(global); break;
							case 2: courseListAllStudentScreen_lecturer(global); break;
							case 3: courseViewAttendanceListScreen_lecturer(global); break;
							case 4: attendanceEditScreen_lecturer(global); break;
							case 5: scoreboardImportFromCSVScreen(global); break;
							case 6: courseViewScoreboardScreen_lecturer(global); break;
							case 7: scoreboardEditScreen(global); break;
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
	cout << "2.View attendance" << endl;
	cout << "3.View schedule" << endl;
	cout << "4.View scoreboard" << endl;
	cout << "5.View profile info" << endl;
	cout << "6.Change password" << endl;
	cout << "7.Log out" << endl;
								*/
							case 1: studentCheckIn(global); break;
							case 2: studentViewAttendance(global); break;
							case 3: studentViewSchedule(global); break;
							case 4: studentViewScoreboard(global); break;
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

void studentImportFromCSVScreen(Global &global) {
	OPENFILENAME ofn;
	char szFile[260]; szFile[0] = '\0';
	char szFileNoDir[100]; szFileNoDir[0] = '\0';

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetConsoleWindow();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);

	ofn.lpstrFilter = "All\0*.*\0CSV File\0*.CSV\0";
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = szFileNoDir;
	ofn.nMaxFileTitle = sizeof(szFileNoDir);
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Choose student file";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn)) {
		system("CLS");
		string fileName = szFile;
		if (importStudentFile(fileName)) {
			cout << "Import complete." << endl;
		}
		else {
			cout << "There is some error." << endl;
			cout << "Contact programmer for further details." << endl;
			cout << "CODE: importStudentFromCSVScreen->importStudentFile" << endl;
		}
		_getch();
	}
}

void studentAddScreen(Global &global) {
	system("CLS");
	cout << "New student" << endl;
	cout << "Press ESC when typing to discard changes & return." << endl;
	Student stu;
	cout << "ID: "; getlineESC(stu.ID);
	if (global.stuList.GetStudentByID(stu.ID, stu)) {
		cout << "This id is already used." << endl;
		_getch();
		return;
	}
	cout << endl;

	int newProfX = 0;
	gotoxy(newProfX, 3); cout << "First Name: ";
	gotoxy(newProfX, 4); cout << "Last Name: ";
	gotoxy(newProfX, 5); cout << "Gender (M/F): ";
	gotoxy(newProfX, 6); cout << "DoB (dd/mm/yyyy): ";
	gotoxy(newProfX, 7); cout << "Class: ";

	string newID, newFirstName, newLastName, newGender, newDoB, newClass;
	gotoxy(newProfX + 12, 3); if (getlineESC(newFirstName)) return;
	gotoxy(newProfX + 11, 4); if (getlineESC(newLastName)) return;
	do {
		gotoxy(newProfX + 14, 5);  cout << "              ";
		gotoxy(newProfX + 14, 5);
		if (getlineESC(newGender)) return;
	} while (newGender[0] != 'M' && newGender[0] != 'm'&&newGender[0] != 'F'&&newGender[0] != 'f');
	if (newGender[0] == 'm') newGender[0] = 'M';
	if (newGender[0] == 'f') newGender[0] = 'F';

	do {
		gotoxy(newProfX + 18, 6);  cout << "              ";
		gotoxy(newProfX + 18, 6);
		if (getlineESC(newDoB)) return;
	} while (!isValidDoB(newDoB));

	//WAIT FOR ClassList.h IMPLEMENTATION
	//For now just enter classNo a.k.a classID
	/*do {
	gotoxy(newProfX + 4, 4); if (getlineESC(newClass)) return;
	} while (!isValidClass(newClass)); */
	string newClassNoStr; 
	gotoxy(newProfX + 7, 7); if (getlineESC(newClassNoStr)) return;

	gotoxy(newProfX, 9); string tmp;
	cout << "Is that ok? [y/n]: "; if (getlineESC(tmp)) return;
	if (tmp[0] == 'y' || tmp[0] == 'Y') {
		stu.firstName = newFirstName;
		stu.lastName = newLastName;
		stu.gender = newGender[0];
		stu.DoB = newDoB;

		Class cla; cla.name = newClassNoStr;
		//Chac chan rang co class no
		global.classList.addClass(cla);
		global.classList.getClassByName(newClassNoStr, cla);

		stu.classID = cla.no;
		global.stuList.AddStudent(stu);

		cout << "Operation complete.";
		_getch();
	}
}

void studentChangeClassScreen(Global &global) {
	system("CLS");
	Student stu;
	string ID;
	cout << "Change class of a student" << endl;
	cout << "Enter student ID: "; if (getlineESC(ID)) return;
	if (global.stuList.GetStudentByID(ID, stu)) {
		cout << "Name: " << stu.firstName << " " << stu.lastName << endl;
		cout << "Gender: " << stu.gender << endl;
		cout << "Date Of Birth: " << stu.DoB << endl;

		Class cla;
		if (!global.classList.getClassByNo(stu.classID, cla)) {
			cout << "DATABASE FAULT!!!" << endl;
			_getch();
			return;
		}
		cout << "Class: " << cla.name << endl;
		cout << endl;

		string newClassStr;
		cout << "Enter new class: "; if (getlineESC(newClassStr)) return;

		string tmp;
		cout << endl << "Is this okay? [y/n] : "; if (getlineESC(tmp)) return;
		if (tmp[0] == 'y' || tmp[0] == 'Y') {
			cla.name = newClassStr;
			global.classList.addClass(cla);
			global.classList.getClassByName(newClassStr, cla);

			global.stuList.ChangeClass(stu.no, cla.no);
			cout << "Operation complete." << endl;
			_getch();
		}

	}
	else {
		cout << "No student with such ID." << endl;
		_getch();
	}
}

void classListScreen(Global &global) {
	system("CLS");
	cout << "ALL CLASSES" << endl;
	cout << "No.\tClass Name" << endl;
	for (unsigned int i = 0; i < global.classList.classes.size(); ++i) {
		cout << i+1 <<"\t"<< global.classList.classes[i].name << endl;
	}
	_getch();
}

void classStudentListScreen(Global &global) {
	system("CLS"); string classStr;
	cout << "CLASS VIEW" << endl;
	cout << "Enter class name: "; getlineESC(classStr);
	Class cla;
	if (global.classList.getClassByName(classStr, cla)) {
		vector<Student> stuVec;
		global.stuList.GetStudentsFromClass(cla.no, stuVec);
		int x_no = 0;
		int x_id = 5;
		int x_firstName = 15;
		int x_lastName = 35;
		int x_gender = 50;
		int x_dob = 58;
		
		int cur_y = 1;
		gotoxy(x_no, cur_y); cout << "NO";
		gotoxy(x_id, cur_y); cout << "ID";
		gotoxy(x_firstName, cur_y); cout << "First name";
		gotoxy(x_lastName, cur_y); cout << "Last name";
		gotoxy(x_gender, cur_y); cout << "Gender";
		gotoxy(x_dob, cur_y); cout << "DoB";
		cur_y++;
		
		for (unsigned int i = 0; i < stuVec.size(); ++i) {
			gotoxy(x_no, cur_y); cout << i + 1;
			gotoxy(x_id, cur_y); cout << stuVec[i].ID;
			gotoxy(x_firstName, cur_y); cout << stuVec[i].firstName;
			gotoxy(x_lastName, cur_y); cout << stuVec[i].lastName;
			gotoxy(x_gender, cur_y); cout << stuVec[i].gender;
			gotoxy(x_dob, cur_y); cout << stuVec[i].DoB;
			cur_y++;
		}
	}
	else {
		cout << "No such class exists." << endl;
	}
	_getch();
}

void semesterListScreenUtil(Global &global, int baseY, vector<Semester> &semVec) { //get out semVec for further usage.
	int x_no = 0, x_year = 5, x_semester = 18;
	gotoxy(x_no, baseY); cout << "No";
	gotoxy(x_year, baseY); cout << "Year";
	gotoxy(x_semester, baseY); cout << "Semester";
	int yOffset = 0;
	semVec.clear();
	for (unsigned int i = 0; i < global.academicYearList.AcademicYears.size(); ++i) {
		AcademicYear year = global.academicYearList.AcademicYears[i];
		vector<Semester> sml = global.semesterList.getSemesterByYear(year.no);
		for (unsigned int j = 0; j < sml.size(); ++j) {
			yOffset++;
			gotoxy(x_no, baseY+yOffset); cout << yOffset;
			gotoxy(x_year, baseY+yOffset); cout << year.name;
			gotoxy(x_semester, baseY+yOffset); cout << sml[j].name;
			semVec.push_back(sml[j]);
		}
	}
}

void academicYearScreenUtil(Global &global, int baseY) {
	int x_no = 0, x_year = 5;
	gotoxy(x_no, baseY); cout << "No";
	gotoxy(x_year, baseY); cout << "Year";
	int yOffset = 0;
	for (unsigned int i = 0; i < global.academicYearList.AcademicYears.size(); ++i) {
		yOffset++;
		gotoxy(x_no, baseY+yOffset); cout << yOffset;
		gotoxy(x_year, baseY+yOffset); cout << global.academicYearList.AcademicYears[i].name;
	}
}

int academicYearSelectScreen(Global &global, string IntroText) { //tra ve academicYearNo
	unsigned int x;
	do {
		system("CLS");
		cout << IntroText << endl;
		academicYearScreenUtil(global, WhereY());
		cout << endl << endl;
		cout << "Enter your choice (0 to exit without selecting): ";
		cin >> x;
	} while (x < 0 || x > (int)global.academicYearList.AcademicYears.size());
	if (x == 0) return -1;
	return global.academicYearList.AcademicYears[x - 1].no;
}
int semesterSelectScreen(Global &global, string IntroText) { //tra ve semesterNo
	unsigned int x;
	vector<Semester> semVec;
	do {
		system("CLS");
		cout << IntroText << endl;
		semesterListScreenUtil(global, WhereY(), semVec);
		cout << endl << endl;
		cout << "Enter your choice (0 to exit without selecting): ";
		cin >> x;
	} while (x<0 || x>semVec.size());
	if (x == 0) return -1;
	return semVec[x - 1].no;
}

void semesterListScreen(Global &global) {
	system("CLS");
	cout << "SEMESTER VIEW" << endl;
	vector<Semester> semVec;
	semesterListScreenUtil(global, 0, semVec);
	_getch();
}

void semesterCreateScreen(Global &global) {
	int yearNo = academicYearSelectScreen(global,"Select an academic year");
	if (yearNo == -1) return;
	system("CLS");
	AcademicYear year; 
	global.academicYearList.GetYearByNo(yearNo, year);
	cout << "Semesters in " << year.name << endl;
	vector<Semester> semVec = global.semesterList.getSemesterByYear(yearNo);
	for (unsigned int i = 0; i < semVec.size(); ++i) {
		cout << i + 1 <<" "<< semVec[i].name << endl;
	}
	string semName;
	cout << endl << "Enter new semester name: "; if (getlineESC(semName)) return;
	Semester sem;
	sem.name = semName;
	sem.yearNo = yearNo;
	if (global.semesterList.addSemester(sem)) {
		cout << "Add complete" << endl;
	}
	else {
		cout << "Semester already exists." << endl;
	}
	_getch();
}

void semesterDeleteScreen(Global &global) {
	int semNo = semesterSelectScreen(global,"Select semester to delete\n"
		"WARNING: Delete all courses in a semester before deleting");
	if (semNo != -1) {
		//Neu con course trong semester nay thi khong cho delete, nguoc lai delete
		//STALLED. WAIT FOR BACK-END
		vector<Course> courseVec;
		global.courseList.GetCoursesBySemester(semNo, courseVec);
		if (courseVec.empty()) {
			if (global.semesterList.deleteSemester(semNo)) {
				cout << "Operation complete." << endl;
			}
			else {
				cout << "SemesterList::deleteSemester fault." << endl;
				cout << "Operation failed." << endl;
			}
		}
		else cout << "Read the warning please" << endl;
		_getch();
	}
	else return;
}
void academicYearCreateScreen(Global &global) {
	system("CLS");
	cout << "ACADEMIC YEAR VIEW" << endl;
	academicYearScreenUtil(global, 0);
	cout << endl << endl << "New academic year name: ";
	string yearNameStr;
	if (getlineESC(yearNameStr)) return;
	AcademicYear year;
	year.name = yearNameStr;
	if (!global.academicYearList.AddYear(year)) {
		cout << "This year name is already existed." << endl;
	}
	else {
		cout << "Operation complete." << endl;
	}
	_getch();
}
void academicYearDeleteScreen(Global &global) {
	system("CLS");
	cout << "Select academic year to delete." << endl;
	cout << "WARNING: Delete ALL semesters in a year before deleting a year" << endl;
	int yearNo = academicYearSelectScreen(global, "Select academic year to delete.\n"
												"WARNING: Delete ALL semesters in a year before deleting a year");
	if (yearNo == -1) return;

	vector<Semester> semVec = global.semesterList.getSemesterByYear(yearNo);
	if (!semVec.empty()) {
		cout << "Read the warning please." << endl;
		cout << "Operation failed." << endl;
	}
	else {
		if (global.academicYearList.RemoveYear(yearNo)) {
			cout << "Operation complete" << endl;
		}
		else {
			cout << "AcademicYearList.RemoveYear failure" << endl;
			cout << "Operation failed" << endl;
		}
	}
	_getch();
}

void courseImportFromCSVScreen(Global &global) {
	int semNo = semesterSelectScreen(global, "Select a semester");

	OPENFILENAME ofn;
	char szFile[260]; szFile[0] = '\0';
	char szFileNoDir[100]; szFileNoDir[0] = '\0';

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetConsoleWindow();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);

	ofn.lpstrFilter = "All\0*.*\0CSV File\0*.CSV\0";
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = szFileNoDir;
	ofn.nMaxFileTitle = sizeof(szFileNoDir);
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Choose course file to import";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn)) {
		system("CLS");
		string fileName = szFile;
		if (global.courseList.importFromFileCSV(fileName, global.classList, global.lecList, semNo)) {
			cout << "Import complete." << endl;
		}
		else {
			cout << "There is some error." << endl;
			cout << "Contact programmer for further details." << endl;
			cout << "CODE: courseImportFromCSVScreen->courseList::importFromFileCSV" << endl;
		}
		_getch();
	}
}

void courseAddScreen(Global &global) {
	int semNo = semesterSelectScreen(global, "Select a semester to add course");
	if (semNo == -1) return;
	system("CLS");
	cout << "NEW COURSE INFO" << endl;
	cout << "ESC at any point to discard changes and exit" << endl;

	string courseID; 
	Course course;
	course.SemNo = semNo;

	cout << "Course ID: "; if (getlineESC(courseID)) return;
	if (global.courseList.GetCourseById(courseID, course)) {
		cout << "This course already exists. Please try again." << endl;
		_getch();
		return;
	}

	course.ID = courseID;
	cout << "Course Name: "; if (getlineESC(course.name)) return;

	string classID;
	Class cla;
	do {
		cout << "Class: "; if (getlineESC(classID)) return;
		if (!global.classList.getClassByName(classID, cla))
			cout << "No such class exists. Please retype."<<endl;
		else break;
	} while (true);
	course.classNo = cla.no;

	string lecacc;
	Lecturer lec;
	cout << "Lecturer Account: "; if (getlineESC(lecacc)) return;
	//Khong bat validate lecturerAcc
	lec.ID = lec.firstName = lec.lastName = lecacc;
	global.lecList.addLecturer(lec);
	
	global.lecList.GetLecByID(lecacc, lec);
	course.lecturerNo = lec.no;

	do {
		cout << "Valid start date: "; if (getlineESC(course.startDate)) return;
	} while (!isValidDoB(course.startDate));
	do {
		cout << "Valid end date: "; if (getlineESC(course.endDate)) return;
	} while (!isValidDoB(course.endDate));

	string dow; //day of week
	do {
		cout << "Date of Week (Mon, Tue... Sun): "; if (getlineESC(dow)) return;
	} while (dow != "Mon" && dow != "Tue" && dow != "Wed" && dow != "Thu"&& dow != "Fri"&& dow != "Sat"&& dow != "Sun");
	course.dayOfWeek = dow;

	int tmp1, tmp2;
	do {
		cout << "Start hour (HH:MM): "; if (getlineESC(course.startHour)) return;
	} while (sscanf(course.startHour.c_str(), "%d:%d", &tmp1, &tmp2)!=2);
	do {
		cout << "End hour (HH:MM): "; if (getlineESC(course.endHour)) return;
	} while (sscanf(course.endHour.c_str(), "%d:%d", &tmp1, &tmp2) != 2);
	
	cout << "Room: "; if (getlineESC(course.room)) return;


	global.courseList.AddCourse(course);
	cout << "Operation complete." << endl;
	_getch();
}

void courseEditScreen(Global &global) {
	system("CLS");
	string ID;
	Course c;
	cout << "COURSE EDIT" << endl;
	cout << "Press ESC during typing to return" << endl;
	cout << "Enter course ID: "; if (getlineESC(ID)) return;
	if (global.courseList.GetCourseById(ID, c)) {
		int x_newprof = 40, y_base = 2;
		cout << "OLD INFO" << endl;
		cout << "ID: " << c.ID << endl;
		cout << "Name: " << c.name << endl;
		Class cla; global.classList.getClassByNo(c.classNo, cla);
		cout << "Class: " << cla.name << endl;
		Lecturer lec; global.lecList.GetLecByNo(c.lecturerNo, lec);
		cout << "Lecturer: " << lec.ID << endl;
		cout << "Start Date: " << c.startDate << endl;
		cout << "End Date: " << c.endDate << endl;
		cout << "Day of Week: " << c.dayOfWeek << endl;
		cout << "Start Hour: " << c.startHour << endl;
		cout << "End Hour: " << c.endHour << endl;
		cout << "Room: " << c.room << endl;

		gotoxy(x_newprof, y_base);
		cout << "NEW INFO" << endl;
		gotoxy(x_newprof, y_base + 1);
		cout << "ID: " << c.ID;
		gotoxy(x_newprof, y_base + 2);
		cout << "Name: ";
		gotoxy(x_newprof, y_base + 3);
		cout << "[Valid] Class: ";
		gotoxy(x_newprof, y_base + 4);
		cout << "Lecturer: ";
		gotoxy(x_newprof, y_base + 5);
		cout << "Start Date (dd/mm/yyyy): ";
		gotoxy(x_newprof, y_base + 6);
		cout << "End Date (dd/mm/yyyy): ";
		gotoxy(x_newprof, y_base + 7);
		cout << "Day of Week (Mon/Tue/...): ";
		gotoxy(x_newprof, y_base + 8);
		cout << "Start Hour (hh:mm): ";
		gotoxy(x_newprof, y_base + 9);
		cout << "End Hour (hh:mm): ";
		gotoxy(x_newprof, y_base + 10);
		cout << "Room: ";

		Semester sem;
		global.semesterList.GetSemesterByNo(c.SemNo, sem);
		gotoxy(x_newprof, y_base + 11);
		cout << "Semester: " << sem.name;

		Course newCourse;
		newCourse.ID = c.ID;
		//gotoxy(x_newprof+4, y_base + 1);
		//if (getlineESC(newCourse.ID)) return;
		gotoxy(x_newprof+6, y_base + 2);
		if (getlineESC(newCourse.name)) return;
		gotoxy(x_newprof+14, y_base + 3);
		do {
			string classStr;
			gotoxy(x_newprof + 15, y_base + 3);
			cout << "                 ";
			gotoxy(x_newprof + 15, y_base + 3);
			if (getlineESC(classStr)) return;
			if (global.classList.getClassByName(classStr, cla)) {
				newCourse.classNo = cla.no;
				break;
			}
		} while (1);

		gotoxy(x_newprof+10, y_base + 4);
		string lecAcc; 
		if (getlineESC(lecAcc)) return;
		lec.ID = lec.firstName = lec.lastName = lecAcc;
		//tao moi neu khong co lecAccount
		global.lecList.addLecturer(lec);
		global.lecList.GetLecByID(lecAcc, lec);
		newCourse.lecturerNo = lec.no;

		do {
			gotoxy(x_newprof + 25, y_base + 5); cout << "            ";
			gotoxy(x_newprof + 25, y_base + 5);
			if (getlineESC(newCourse.startDate)) return;
		} while (!isValidDoB(newCourse.startDate));
	
		do {
			gotoxy(x_newprof + 23, y_base + 6); cout << "            ";
			gotoxy(x_newprof + 23, y_base + 6);
			if (getlineESC(newCourse.endDate)) return;
		} while (!isValidDoB(newCourse.endDate));

		string tmp;
		do {
			gotoxy(x_newprof + 27, y_base + 7); cout << "            ";
			gotoxy(x_newprof + 27, y_base + 7);
			if (getlineESC(tmp)) return;
		} while (tmp != "Mon" && tmp != "Tue" &&tmp != "Wed" &&tmp != "Thu" &&tmp != "Fri" &&tmp != "Sat" &&tmp != "Sun");
		newCourse.dayOfWeek = tmp;

		int tmp1, tmp2;
		do {
			gotoxy(x_newprof + 20, y_base + 8); cout << "             ";
			gotoxy(x_newprof + 20, y_base + 8);
			if (getlineESC(newCourse.startHour)) return;
		} while (sscanf(newCourse.startHour.c_str(), "%d:%d", &tmp1, &tmp2) != 2);

		do {
			gotoxy(x_newprof + 18, y_base + 9); cout << "             ";
			gotoxy(x_newprof + 18, y_base + 9);
			if (getlineESC(newCourse.endHour)) return;
		} while (sscanf(newCourse.endHour.c_str(), "%d:%d", &tmp1, &tmp2) != 2);

		gotoxy(x_newprof+6, y_base + 10);
		if (getlineESC(newCourse.room)) return;

		newCourse.SemNo = c.SemNo;

		if (global.courseList.Update(c.no, newCourse)) {
			cout << "Info update complete." << endl;
			_getch();
			return;
		}
		else {
			cout << "ERROR: courseList.Update" << endl;
			cout << "Operation failed." << endl;
			_getch();
			return;
		}
	}
	else {
		cout << "No such course exists." << endl;
		cout << "Please try again" << endl;
		_getch();
		return;
	}

}
void courseRemoveScreen(Global &global) {
	system("CLS");
	string ID;
	Course c;
	cout << "COURSE DELETE" << endl;
	cout << "Enter course ID: "; if (getlineESC(ID)) return;
	if (global.courseList.GetCourseById(ID, c)) {
		cout << "Name: " << c.name << endl;
		Class cla; global.classList.getClassByNo(c.classNo, cla);
		cout << "Class: " << cla.name << endl;
		Lecturer lec; global.lecList.GetLecByNo(c.lecturerNo, lec);
		cout << "Lecturer: " << lec.ID << endl;
		cout << "Start Date: " << c.startDate << endl;
		cout << "End Date: " << c.endDate << endl;
		cout << "Day of Week: " << c.dayOfWeek << endl;
		cout << "Start Hour: " << c.startHour << endl;
		cout << "End Hour: " << c.endHour << endl;
		cout << "Room: " << c.room << endl;
		Semester sem; global.semesterList.GetSemesterByNo(c.SemNo, sem);
		AcademicYear year; global.academicYearList.GetYearByNo(sem.yearNo, year);
		cout << "Semester: " << sem.name << endl;
		cout << "Year: " << year.name << endl;

		cout << endl;
		cout << "Are you sure you want to delete this course? [y/n]: ";
		string tmp; if (getlineESC(tmp)) return;
		if (tmp[0] == 'y' || tmp[0] == 'Y') {
			global.courseList.Remove(c.no);
			cout << "Remove complete." << endl;
			_getch();
		}
	}
	else {
		cout << "No such course exists." << endl;
		cout << "Please try again" << endl;
		_getch();
		return;
	}
}

//use: currentStudent
void studentUnenrollScreen(Global &global) {
	do {
		system("CLS");
		cout << global.currentStudent.ID<<" : "<< global.currentStudent.firstName << " " << global.currentStudent.lastName << endl;
		vector<Course> courseVec;
		global.courseStudentList.GetCoursesOfStudent(global.currentStudent.no, courseVec, global.courseList, global.stuList);
		if (courseVec.empty()) {
			cout << "Sorry, no course to un-enroll." << endl;
			_getch();
			return;
		}
		else {
			cout << "Choose a course to un-enroll (0 to return)" << endl;
			int x_no = 0, x_id = 4, x_name = 15, x_lec = 55, y_base = WhereY();
			gotoxy(x_no, y_base); cout << "NO";
			gotoxy(x_id, y_base); cout << "ID";
			gotoxy(x_name, y_base); cout << "Name";
			gotoxy(x_lec, y_base); cout << "Lecturer";
			for (unsigned int i = 0; i < courseVec.size(); ++i) {
				gotoxy(x_no, y_base + 1 + i); cout << i + 1;
				gotoxy(x_id, y_base + 1 + i); cout << courseVec[i].ID;
				gotoxy(x_name, y_base + 1 + i); cout << courseVec[i].name;

				Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
				gotoxy(x_lec, y_base + 1 + i); cout << lec.firstName << " " << lec.lastName;
			}
			cout << endl;
			int x;
			cout << "Enter your choice (NO UNDO): "; cin >> x;
			if (x == 0 || x > (int)courseVec.size()) return;

			if (global.courseStudentList.DropStudent(global.currentStudent.no, courseVec[x - 1].no, global.courseList, global.stuList)) {
				cout << "Remove complete. Any key to continue" << endl;
				_getch();
			}
			else {
				cout << "ERROR: courseStudentList::DropStudent return false" << endl;
				_getch();
			}
		}
	} while (1);
}

void courseStudentRemoveScreen(Global &global) {
	system("CLS");
	cout << "Unenroll a student" << endl;
	string stuID;
	cout << "Enter student ID: "; if (getlineESC(stuID)) return;
	if (global.stuList.GetStudentByID(stuID, global.currentStudent)) {
		studentUnenrollScreen(global);
	}
	else {
		cout << "No such student exists." << endl;
		_getch();
		return;
	}
}

//Enroll a student
void courseStudentAddScreen(Global &global) {
	system("CLS");
	cout << "Enroll a student" << endl;
	string stuID;
	cout << "Enter student ID: "; if (getlineESC(stuID)) return;
	if (global.stuList.GetStudentByID(stuID, global.currentStudent)) {
		int semNo;
		vector<Course> courseVec;
		semesterListAllCourseScreenUtil(global, courseVec, semNo, "AVAILABLE COURSES for " + global.currentStudent.ID
			+ " : " + global.currentStudent.firstName + " " + global.currentStudent.lastName, 0);
		if (courseVec.empty()) {
			cout << "Any key to return" << endl;
			_getch();
			return;
		}

		cout << endl << endl;
		int x;
		cout << "Enter your choice: "; cin >> x;
		if (x == 0 || x>(int)courseVec.size()) return;
		
		if (global.courseStudentList.AddStudentToCourse(courseVec[x - 1].no,
			global.currentStudent.no,
			global.courseList,
			global.stuList)) {

			cout << "Enroll complete." << endl;
			_getch();
		}
		else {
			cout << "Already enroll in this course. No need to re-enroll" << endl;
			_getch();
		}
	}
	else {
		cout << "No such student exists." << endl;
		_getch();
		return;
	}

}

void semesterListAllCourseScreenUtil(Global &global, vector<Course> &courseVec, int &semNo, string IntroText, bool getch) {
	semNo = semesterSelectScreen(global, "Select a semester");
	if (semNo == -1) return;
	global.courseList.GetCoursesBySemester(semNo, courseVec);
	system("CLS");
	cout << IntroText << endl;
	//1 CS162 Intro Science II dbTien 18ctt5 01/03/2000->30/04/2000 Wed 08:00->11:00
	int x_no = 0, x_ID = 5, x_name = 15, x_lecturer = 45, x_class = 65, x_date = 15, x_hour = 45, x_dow = 65;
	int cur_y = WhereY();

	if (courseVec.size() == 0) {
		cout << "Sorry. There is no course available." << endl;
		if (getch)
			_getch();
		return;
	}
	else
	for (unsigned int i = 0; i < courseVec.size(); ++i) {
		gotoxy(x_no, cur_y); cout << i + 1;
		gotoxy(x_ID, cur_y); cout << courseVec[i].ID;
		gotoxy(x_name, cur_y); cout << courseVec[i].name;

		Lecturer lec; 
		global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		gotoxy(x_lecturer, cur_y); cout << lec.firstName << " " << lec.lastName;

		Class cla;
		global.classList.getClassByNo(courseVec[i].classNo, cla);
		gotoxy(x_class, cur_y); cout << cla.name;
		gotoxy(x_date, cur_y + 1); cout << courseVec[i].startDate << " -> " << courseVec[i].endDate;
		gotoxy(x_hour, cur_y + 1); cout << courseVec[i].startHour << " - " << courseVec[i].endHour;
		gotoxy(x_dow, cur_y + 1); cout << courseVec[i].dayOfWeek;
		cur_y += 2;
	}
	if (getch)
		_getch();
}
void semesterListAllCourseScreen_staff(Global &global) {
	vector<Course> courseVec;
	int semNo;
	semesterListAllCourseScreenUtil(global, courseVec, semNo, "ALL COURSE VIEW", 1);
}

void courseListAllStudentScreen(Global &global) {
	int semNo;
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil(global, courseVec, semNo, "Select a course", 0);
	if (courseVec.empty()) {
		cout << "Any key to return." << endl;
		_getch();
		return;
	}
	unsigned int x;
	cout << endl << endl << "Enter your choice (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	vector<Student> stuVec;
	global.courseStudentList.GetStudentOfCourse(courseSelected.no, stuVec, global.stuList, global.courseList);
	
	system("CLS");
	cout << "ENROLLED VIEW" << endl;
	cout << "Course " << courseSelected.ID << " " << courseSelected.name << endl;
	if (stuVec.empty()) {
		cout << "No student enrolled in this course.\n" << endl;
	}
	else {
		int x_no = 0, x_id = 5, x_name = 25, cur_y = WhereY();
		gotoxy(x_no, cur_y); cout << "NO";
		gotoxy(x_id, cur_y); cout << "ID";
		gotoxy(x_name, cur_y); cout << "NAME";
		cur_y++;
		for (unsigned int i = 0; i < stuVec.size(); ++i) {
			gotoxy(x_no, cur_y); cout << i + 1;
			gotoxy(x_id, cur_y); cout << stuVec[i].ID;
			gotoxy(x_name, cur_y); cout << stuVec[i].firstName<<" "<<stuVec[i].lastName;
			cur_y++;
		}
	}
	_getch();
}

void lecturerAddScreen(Global &global) {
	system("CLS");
	cout << "New Lecturer account (ESC to return)" << endl;
	string lecID;
	cout << "Enter ID: "; if (getlineESC(lecID)) return;
	Lecturer lec;
	if (global.lecList.GetLecByID(lecID, lec)) {
		cout << "This ID is already exists. Please try again." << endl;
		_getch();
		return;
	}
	lec.ID = lecID;
	cout << "Enter first name: "; if (getlineESC(lec.firstName)) return;
	cout << "Enter last name: "; if (getlineESC(lec.lastName)) return;
	global.lecList.addLecturer(lec);
	cout << "Add complete. His default password is now ""123456""" << endl;
	cout << "Tell him to change the password" << endl;
	_getch();
}

void lecturerListScreen(Global &global) {
	system("CLS");
	cout << "ALL LECTURER VIEW" << endl;

	if (global.lecList.lecturers.empty()) {
		cout << "No lecturer yet." << endl;
		_getch();
		return;
	}
	int x_no = 0, x_acc = 5, x_firstName = 25, x_lastName = 45, cur_y = WhereY();
	gotoxy(x_no, cur_y); cout << "NO";
	gotoxy(x_acc, cur_y); cout << "ACCOUNT";
	gotoxy(x_firstName, cur_y); cout << "First Name";
	gotoxy(x_lastName, cur_y); cout << "Last Name";
	cur_y++;
	for (unsigned int i = 0; i < global.lecList.lecturers.size(); ++i) {
		gotoxy(x_no, cur_y); cout << i + 1;
		gotoxy(x_acc, cur_y); cout << global.lecList.lecturers[i].ID;
		gotoxy(x_firstName, cur_y); cout << global.lecList.lecturers[i].firstName;
		gotoxy(x_lastName, cur_y); cout << global.lecList.lecturers[i].lastName;
		cur_y++;
	}
	_getch();
}

bool courseViewAttendanceListScreenUtil(Global &global, Course selectedCourse, bool getch) {
	system("CLS");
	int numWeek = selectedCourse.NumberOfWeek();
	if (numWeek == 0) {
		cout << "No attendance list for a course which have 0 week" << endl;
		if (getch)
			_getch();
		return 1;
	}
	vector<Student> vecStu;
	global.courseStudentList.GetStudentOfCourse(selectedCourse.no,
		vecStu,
		global.stuList,
		global.courseList);
	cout << "ATTENDANCE : " << selectedCourse.ID << " " << selectedCourse.name << endl;

	if (vecStu.empty()) {
		cout << "No student enrolled in this course" << endl;
		if (getch)
			_getch();
		return 1;
	}
	cout << "P for Present, A for Absent" << endl;

	int x_id = 0, x_name = 10;
	int *x_w = new int[numWeek+1];
	int cur_y = WhereY();
	x_w[1] = 50;
	for (int i = 2; i <= numWeek; ++i) x_w[i] = x_w[i - 1] + 4;
	
	gotoxy(x_id,cur_y); cout << "ID";
	gotoxy(x_name, cur_y); cout << "Name";
	for (int i = 1; i <= numWeek; ++i) {
		gotoxy(x_w[i], cur_y);
		cout << "W" << i;
	}
	cur_y++;

	for (unsigned int i = 0; i < vecStu.size(); ++i) {
		gotoxy(x_id, cur_y); cout << vecStu[i].ID;
		gotoxy(x_name, cur_y); cout << vecStu[i].firstName<<" "<<vecStu[i].lastName;
		for (int j = 1; j <= numWeek; ++j) {
			gotoxy(x_w[j], cur_y);
			Attendance att;
			string attt = global.attendanceList.getAttendance(j, selectedCourse.no, vecStu[i].no, att);
			cout << attt;
		}
		cur_y++;
	}
	if (getch)
		_getch();
	delete[] x_w;
	return 0;
}

void courseViewAttendanceListScreen_staff(Global &global) {
	//Select a course.
	int semNo;
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil(global, courseVec, semNo, "Select a course", 0);

	if (courseVec.empty()) {
		cout << "Any key to return." << endl;
		_getch();
		return;
	}

	unsigned int x;
	cout << endl << endl << "Select a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	if (courseViewAttendanceListScreenUtil(global, courseSelected, 0)) {
		_getch();
		return;
	}
	cout << endl << endl;
	cout << "Press Enter to export to CSV file, any other keys to return." << endl;
	int ch = _getch();
	if (ch == VK_RETURN) {
		OPENFILENAME ofn;
		char szFile[260]; szFile[0] = '\0';
		char szFileNoDir[100]; szFileNoDir[0] = '\0';

		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetConsoleWindow();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);

		ofn.lpstrFilter = "All\0*.*\0CSV File (*.csv)\0*.CSV\0";
		ofn.nFilterIndex = 2;
		ofn.lpstrFileTitle = szFileNoDir;
		ofn.nMaxFileTitle = sizeof(szFileNoDir);
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = "Export attendance list to...";
		ofn.lpstrDefExt = "csv";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileName(&ofn)) {
			string fileName = szFile;
			global.attendanceList.exportToFileCSV(fileName,
				global.stuList,
				courseSelected.no,
				global.courseList,
				global.courseStudentList);
				cout << "Export complete." << endl;
			_getch();
		}
	}
}

//staff va lecturer se dung chung
//return 1 neu enrolledStudentList khong co gi.
bool courseViewScoreboardScreenUtil(Global &global, Course courseSelected, bool getch) {
	system("CLS");

	//Danh sach nguoi hoc
	vector<Student> stuVec;
	global.courseStudentList.GetStudentOfCourse(courseSelected.no, stuVec, global.stuList, global.courseList);

	cout << "Scoreboard of " << courseSelected.ID << " : " << courseSelected.name << endl;

	if (stuVec.empty()) {
		cout << endl << "No student enrolled in this course." << endl;
		if (getch)
			_getch();
		return 1;
	}

	int x_no = 0, x_id=4, x_name=14, x_midterm = 54, x_final = 60, x_lab = 66, x_bonus = 72, cur_y = WhereY();
	gotoxy(x_no, cur_y); cout << "NO";
	gotoxy(x_id, cur_y); cout << "ID";
	gotoxy(x_name, cur_y); cout << "Name";
	gotoxy(x_midterm, cur_y); cout << "Mid";
	gotoxy(x_final, cur_y); cout << "Final";
	gotoxy(x_lab, cur_y); cout << "Lab";
	gotoxy(x_bonus, cur_y); cout << "Bonus";
	cur_y++;

	for (unsigned int i = 0; i < stuVec.size(); ++i) {
		gotoxy(x_no, cur_y); cout << i+1;
		gotoxy(x_id, cur_y); cout << stuVec[i].ID;
		gotoxy(x_name, cur_y); cout << stuVec[i].firstName << " " << stuVec[i].lastName;

		//Lay diem
		Scoreboard sc = global.scoreboardList.GetScoreboard(stuVec[i].no, courseSelected.no);

		gotoxy(x_midterm, cur_y); cout << sc.midterm;
		gotoxy(x_final, cur_y); cout << sc.final;
		gotoxy(x_lab, cur_y); cout << sc.lab;
		gotoxy(x_bonus, cur_y); cout << sc.bonus;
		cur_y++;
	}
	if (getch)
		_getch();
	return 0;
}

void courseViewScoreboardScreen_staff(Global &global) {
	//Select a course.
	int semNo;
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil(global, courseVec, semNo, "Select a course", 0);
	if (semNo == -1) return;
	if (courseVec.empty()) {
		cout << "Any key to return" << endl;
		_getch();
		return;
	}

	unsigned int x;
	cout << endl << endl << "Select a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];
	if (courseViewScoreboardScreenUtil(global, courseSelected, 0)) {
		cout << "Any key to return" << endl;
		_getch();
		return;
	}

	cout << endl << endl << "Press Enter to export to csv file, any other key to return." << endl;
	int ch = _getch();
	if (ch == VK_RETURN) {
		OPENFILENAME ofn;
		char szFile[260]; szFile[0] = '\0';
		char szFileNoDir[100]; szFileNoDir[0] = '\0';

		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetConsoleWindow();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);

		ofn.lpstrFilter = "All\0*.*\0CSV File (*.csv)\0*.CSV\0";
		ofn.nFilterIndex = 2;
		ofn.lpstrFileTitle = szFileNoDir;
		ofn.nMaxFileTitle = sizeof(szFileNoDir);
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = "Export scoreboard to...";
		ofn.lpstrDefExt = "csv";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileName(&ofn)) {
			string fileName = szFile;
			if (global.scoreboardList.ExportCsv(courseSelected.no, fileName)) {
				cout << "Export complete." << endl;
				_getch();
			}
			else {
				cout << "ERROR: scoreboardList::ExportCsv" << endl;
				_getch();
			}
		}
	}
}

void semesterListAllCourseScreenUtil_lecturer(Global &global, vector<Course> &courseVec, bool getch) {
	system("CLS");

	global.courseList.getCourseOfLecturer(global.currentLecturer.no, courseVec);
	if (courseVec.empty()) {
		cout << "Sorry, there is no course available." << endl;
		cout << "Contact the staff to create new course." << endl;
		if (getch)
			_getch();
		return;
	}
	cout << global.currentLecturer.firstName << " " << global.currentLecturer.lastName << "'s courses" << endl;

	//1,cs162,intro to prozip I(18ctt5),3/2/1930->19/5/1930,
	//		  <year> <sem>				07:30->09:30 Wed at I64
	int x_no = 0, x_ID = 5, x_name = 15, x_date = 55, x_hour = 55, x_sem=15;
	int cur_y = WhereY();

	cout << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i) {
		gotoxy(x_no, cur_y); cout << i + 1;
		gotoxy(x_ID, cur_y); cout << courseVec[i].ID;
		Class cla; global.classList.getClassByNo(courseVec[i].no, cla);
		gotoxy(x_name, cur_y); cout << courseVec[i].name << " (" << cla.name << ") ";
		gotoxy(x_date, cur_y); cout << courseVec[i].startDate << " -> " << courseVec[i].endDate;

		Semester sem; global.semesterList.GetSemesterByNo(courseVec[i].SemNo, sem);
		AcademicYear year; global.academicYearList.GetYearByNo(sem.yearNo, year);
		gotoxy(x_sem, cur_y + 1); cout << year.name << " " << sem.name;
		gotoxy(x_hour, cur_y + 1); cout << courseVec[i].startHour << " -> " << courseVec[i].endHour << " at " << courseVec[i].room;
		cur_y += 2;
	}
	if (getch)
		_getch();
}

void semesterListAllCourseScreen_lecturer(Global &global) {
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil_lecturer(global, courseVec, true);
}

void courseListAllStudentScreen_lecturer(Global &global) {
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil_lecturer(global, courseVec, false);
	unsigned int x = 0;
	cout << endl;
	cout << "Choose a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	vector<Student> stuVec;
	global.courseStudentList.GetStudentOfCourse(courseSelected.no, stuVec, global.stuList, global.courseList);

	system("CLS");
	cout << "Course " << courseSelected.ID << " " << courseSelected.name << endl;
	if (stuVec.empty()) {
		cout << "No student enrolled in this course.\n" << endl;
	}
	else {
		int x_no = 0, x_id = 5, x_name = 25, cur_y = WhereY();
		gotoxy(x_no, cur_y); cout << "NO";
		gotoxy(x_id, cur_y); cout << "ID";
		gotoxy(x_name, cur_y); cout << "NAME";
		cur_y++;
		for (unsigned int i = 0; i < stuVec.size(); ++i) {
			gotoxy(x_no, cur_y); cout << i + 1;
			gotoxy(x_id, cur_y); cout << stuVec[i].ID;
			gotoxy(x_name, cur_y); cout << stuVec[i].firstName << " " << stuVec[i].lastName;
			cur_y++;
		}
	}
	_getch();
}

void courseViewAttendanceListScreen_lecturer(Global &global) {
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil_lecturer(global, courseVec, false);
	unsigned int x = 0;
	cout << endl;
	cout << "Choose a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	if (courseViewAttendanceListScreenUtil(global, courseSelected, 0)) {
		_getch();
		return;
	}
	cout << endl << endl;
	cout << "Press Enter to export to CSV file, any other keys to return." << endl;
	int ch = _getch();
	if (ch == VK_RETURN) {
		OPENFILENAME ofn;
		char szFile[260]; szFile[0] = '\0';
		char szFileNoDir[100]; szFileNoDir[0] = '\0';

		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetConsoleWindow();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);

		ofn.lpstrFilter = "All\0*.*\0CSV File (*.csv)\0*.CSV\0";
		ofn.nFilterIndex = 2;
		ofn.lpstrFileTitle = szFileNoDir;
		ofn.nMaxFileTitle = sizeof(szFileNoDir);
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = "Export attendance list to...";
		ofn.lpstrDefExt = "csv";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileName(&ofn)) {
			string fileName = szFile;
			global.attendanceList.exportToFileCSV(fileName,
				global.stuList,
				courseSelected.no,
				global.courseList,
				global.courseStudentList);
			cout << "Export complete." << endl;
			_getch();
		}
	}
}

void attendanceEditScreen_lecturer(Global &global) {
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil_lecturer(global, courseVec, false);
	unsigned int x = 0;
	cout << endl;
	cout << "Choose a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	vector<Student> stuVec;
	global.courseStudentList.GetStudentOfCourse(courseSelected.no, stuVec, global.stuList, global.courseList);

	system("CLS");
	cout << "EDIT ATTENDANCE" << endl;
	cout << "Course " << courseSelected.ID << " " << courseSelected.name << endl;
	if (stuVec.empty()) {
		cout << "No student enrolled in this course.\n" << endl;
		_getch();
		return;
	}
	else {
		int x_no = 0, x_id = 5, x_name = 25, cur_y = WhereY();
		gotoxy(x_no, cur_y); cout << "NO";
		gotoxy(x_id, cur_y); cout << "ID";
		gotoxy(x_name, cur_y); cout << "NAME";
		cur_y++;
		for (unsigned int i = 0; i < stuVec.size(); ++i) {
			gotoxy(x_no, cur_y); cout << i + 1;
			gotoxy(x_id, cur_y); cout << stuVec[i].ID;
			gotoxy(x_name, cur_y); cout << stuVec[i].firstName << " " << stuVec[i].lastName;
			cur_y++;
		}
	}
	cout << endl << endl;
	string stuID;
	bool reallyEnrolled = 0;
	while (!reallyEnrolled) {
		cout << "Enter enrolled student ID (ESC to return): "; if (getlineESC(stuID)) return;

		for (unsigned int i = 0; i < stuVec.size(); ++i) {
			if (stuVec[i].MatchId(stuID)) {
				reallyEnrolled=1; break;
			}
		}
	}
	Student stu;
	global.stuList.GetStudentByID(stuID, stu);

	int weekNo;
	do {
		cout << "Enter valid week number (0 to return): "; cin.clear();
		cin >> weekNo;
		if (weekNo == 0) return;
		if (weekNo >= 1 && weekNo <= courseSelected.NumberOfWeek()) {
			break;
		}
	} while (1);
	string yum;
	do {
		cout << "Enter ""A"" for absent, ""P"" for present: "; if (getlineESC(yum)) return;
	} while (yum != "A" && yum != "P" && yum!="a" && yum!="p");
	if (yum == "a") yum = "A";
	if (yum == "p") yum = "P";
	global.attendanceList.addOrUpdateAttendance(weekNo, courseSelected.no, stu.no, yum);
	cout << "Attendance update complete." << endl;
	_getch();
}

void scoreboardImportFromCSVScreen(Global &global) {
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil_lecturer(global, courseVec, false);
	unsigned int x = 0;
	cout << endl;
	cout << "Choose a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	OPENFILENAME ofn;
	char szFile[260]; szFile[0] = '\0';
	char szFileNoDir[100]; szFileNoDir[0] = '\0';

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetConsoleWindow();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);

	ofn.lpstrFilter = "All\0*.*\0CSV File\0*.CSV\0";
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = szFileNoDir;
	ofn.nMaxFileTitle = sizeof(szFileNoDir);
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Choose scoreboard file";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn)) {
		system("CLS");
		string fileName = szFile;
		if (global.scoreboardList.ImportFromCSV(fileName, courseSelected.no, global.stuList)) {
			cout << "Import complete." << endl;
		}
		else {
			cout << "There is some error." << endl;
			cout << "Contact programmer for further details." << endl;
			cout << "CODE: scoreboardImportFromCSVScreen->scoreboardList::ImportFromCSV" << endl;
		}
		_getch();
	}
}


void scoreboardEditScreen(Global &global) {
	vector<Course> courseVec;
	semesterListAllCourseScreenUtil_lecturer(global, courseVec, false);
	unsigned int x = 0;
	cout << endl;
	cout << "Choose a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	vector<Student> stuVec;
	global.courseStudentList.GetStudentOfCourse(courseSelected.no, stuVec, global.stuList, global.courseList);

	system("CLS");
	cout << "EDIT ATTENDANCE" << endl;
	cout << "Course " << courseSelected.ID << " " << courseSelected.name << endl;
	if (stuVec.empty()) {
		cout << "No student enrolled in this course.\n" << endl;
		_getch();
		return;
	}
	else {
		int x_no = 0, x_id = 5, x_name = 25, cur_y = WhereY();
		gotoxy(x_no, cur_y); cout << "NO";
		gotoxy(x_id, cur_y); cout << "ID";
		gotoxy(x_name, cur_y); cout << "NAME";
		cur_y++;
		for (unsigned int i = 0; i < stuVec.size(); ++i) {
			gotoxy(x_no, cur_y); cout << i + 1;
			gotoxy(x_id, cur_y); cout << stuVec[i].ID;
			gotoxy(x_name, cur_y); cout << stuVec[i].firstName << " " << stuVec[i].lastName;
			cur_y++;
		}
	}
	cout << endl << endl;
	string stuID;
	bool reallyEnrolled = 0;
	while (!reallyEnrolled) {
		cout << "Enter enrolled student ID (ESC to return): "; if (getlineESC(stuID)) return;

		for (unsigned int i = 0; i < stuVec.size(); ++i) {
			if (stuVec[i].MatchId(stuID)) {
				reallyEnrolled = 1; break;
			}
		}
	}
	Student stu;
	global.stuList.GetStudentByID(stuID, stu);

	Scoreboard sc;
	sc.courseNo = courseSelected.no;
	sc.studentNo = stu.no;
	cout << "If there is no score yet, just enter 0" << endl;
	do {
		cout << "Score must be from 0 to 10, inclusive" << endl;
		cout << "Enter mid-term: "; cin >> sc.midterm;
		cout << "Enter final: "; cin >> sc.final;
		cout << "Enter lab: "; cin >> sc.lab;
		cout << "Enter bonus: "; cin >> sc.bonus;
	} while (!sc.isValid());

	global.scoreboardList.AddOrUpdate(sc);
	cout << "Scoreboard update complete." << endl;
	_getch();
}

void courseViewScoreboardScreen_lecturer(Global &global) {
	//Select a course.

	vector<Course> courseVec;
	semesterListAllCourseScreenUtil_lecturer(global, courseVec, false);

	if (courseVec.empty()) {
		cout << "Any key to return" << endl;
		_getch();
		return;
	}

	unsigned int x = 0;
	cout << endl;
	cout << "Choose a course (0 to return): "; cin >> x;
	if (x == 0 || x > courseVec.size()) return;
	Course courseSelected = courseVec[x - 1];

	if (courseViewScoreboardScreenUtil(global, courseSelected, 0)) {
		cout << "Any key to return" << endl;
		_getch();
		return;
	}

	cout << endl << endl << "Press Enter to export to csv file, any other key to return." << endl;
	int ch = _getch();
	if (ch == VK_RETURN) {
		OPENFILENAME ofn;
		char szFile[260]; szFile[0] = '\0';
		char szFileNoDir[100]; szFileNoDir[0] = '\0';

		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetConsoleWindow();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);

		ofn.lpstrFilter = "All\0*.*\0CSV File (*.csv)\0*.CSV\0";
		ofn.nFilterIndex = 2;
		ofn.lpstrFileTitle = szFileNoDir;
		ofn.nMaxFileTitle = sizeof(szFileNoDir);
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = "Export scoreboard to...";
		ofn.lpstrDefExt = "csv";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileName(&ofn)) {
			string fileName = szFile;
			if (global.scoreboardList.ExportCsv(courseSelected.no, fileName)) {
				cout << "Export complete." << endl;
				_getch();
			}
			else {
				cout << "ERROR: scoreboardList::ExportCsv" << endl;
				_getch();
			}
		}
	}
}

//use:currentStudent
void studentViewSchedule(Global &global){
	system("CLS");
	cout << "SCHEDULE" << endl;
	vector<Course> courseVec;
	global.courseStudentList.GetCoursesOfStudent(global.currentStudent.no,
		courseVec,
		global.courseList,
		global.stuList);

	cout << "MON" << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i)
	if (courseVec[i].dayOfWeek == "Mon") {
		Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		cout << courseVec[i].ID << " " << courseVec[i].name << ". Lecturer: " << lec.firstName << " " << lec.lastName << ". Time: "
			<< courseVec[i].startHour << " to " << courseVec[i].endHour << endl;
	}
	cout << endl;

	cout << "TUE" << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i)
	if (courseVec[i].dayOfWeek == "Tue") {
		Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		cout << courseVec[i].ID << " " << courseVec[i].name << ". Lecturer: " << lec.firstName << " " << lec.lastName << ". Time: "
			<< courseVec[i].startHour << " to " << courseVec[i].endHour << endl;
	}
	cout << endl;

	cout << "WED" << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i)
	if (courseVec[i].dayOfWeek == "Wed") {
		Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		cout << courseVec[i].ID << " " << courseVec[i].name << ". Lecturer: " << lec.firstName << " " << lec.lastName << ". Time: "
			<< courseVec[i].startHour << " to " << courseVec[i].endHour << endl;
	}
	cout << endl;

	cout << "THU" << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i)
	if (courseVec[i].dayOfWeek == "Thu") {
		Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		cout << courseVec[i].ID << " " << courseVec[i].name << ". Lecturer: " << lec.firstName << " " << lec.lastName << ". Time: "
			<< courseVec[i].startHour << " to " << courseVec[i].endHour << endl;
	}
	cout << endl;

	cout << "FRI" << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i)
	if (courseVec[i].dayOfWeek == "Fri") {
		Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		cout << courseVec[i].ID << " " << courseVec[i].name << ". Lecturer: " << lec.firstName << " " << lec.lastName << ". Time: "
			<< courseVec[i].startHour << " to " << courseVec[i].endHour << endl;
	}
	cout << endl;

	cout << "SAT" << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i)
	if (courseVec[i].dayOfWeek == "Sat") {
		Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		cout << courseVec[i].ID << " " << courseVec[i].name << ". Lecturer: " << lec.firstName << " " << lec.lastName << ". Time: "
			<< courseVec[i].startHour << " to " << courseVec[i].endHour << endl;
	}
	cout << endl;

	_getch();
}

//use:currentStudent
void studentViewScoreboard(Global &global) {
	system("CLS");
	cout << "SCOREBOARD : " << global.currentStudent.firstName << " " << global.currentStudent.lastName << endl;
	vector<Course> courseVec;
	global.courseStudentList.GetCoursesOfStudent(global.currentStudent.no,
		courseVec,
		global.courseList,
		global.stuList);
	if (courseVec.empty()) {
		cout << "You are not enrolled in any course." << endl;
		cout << "So, no scoreboard." << endl;
		_getch();
		return;
	}
	int x_course = 0, x_midterm = 50, x_final = 56, x_lab = 62, x_bonus = 68;
	int cur_y = WhereY();

	gotoxy(x_course, cur_y); cout << "Course";
	gotoxy(x_midterm, cur_y); cout << "Mid";
	gotoxy(x_final, cur_y); cout << "Final";
	gotoxy(x_lab, cur_y); cout << "Lab";
	gotoxy(x_bonus, cur_y); cout << "Bonus";
	cur_y++;

	for (unsigned int i = 0; i < courseVec.size(); ++i) {
		gotoxy(x_course, cur_y); cout << courseVec[i].ID << " - " << courseVec[i].name;
		Scoreboard sc = global.scoreboardList.GetScoreboard(global.currentStudent.no, courseVec[i].no);
		gotoxy(x_midterm, cur_y); cout << sc.midterm;
		gotoxy(x_final, cur_y); cout << sc.final;
		gotoxy(x_lab, cur_y); cout << sc.lab;
		gotoxy(x_bonus, cur_y); cout << sc.bonus;
		cur_y++;
	}
	_getch();
}

//use:currentStudent
void studentViewAttendance(Global &global) {
	system("CLS");
	cout << "ATTENDANCE : " << global.currentStudent.firstName << " " << global.currentStudent.lastName << endl;
	vector<Course> courseVec;
	global.courseStudentList.GetCoursesOfStudent(global.currentStudent.no,
		courseVec,
		global.courseList,
		global.stuList);
	if (courseVec.empty()) {
		cout << "You are not enrolled in any course." << endl;
		cout << "So, no attendance list." << endl;
		_getch();
		return;
	}

	int noWeek = 0;
	for (Course i: courseVec)
	if (i.NumberOfWeek() > noWeek)
		noWeek = i.NumberOfWeek();

	int x_course = 0;
	int *x_w = new int[noWeek+1];
	x_w[1] = 45;
	for (int i = 2; i <= noWeek; ++i) x_w[i] = x_w[i - 1] + 4;
	int cur_y = WhereY();

	gotoxy(x_course, cur_y); cout << "Course";
	for (int i = 1; i <= noWeek; ++i) {
		gotoxy(x_w[i], cur_y); cout << "W" << i;
	}
	cur_y++;

	for (unsigned int i = 0; i < courseVec.size(); ++i) {
		gotoxy(x_course, cur_y); cout << courseVec[i].ID<<" - "<<courseVec[i].name;
		for (int j = 1; j <= noWeek; ++j) {
			Attendance att;
			string yum = global.attendanceList.getAttendance(j,
				courseVec[i].no,
				global.currentStudent.no,
				att);
			gotoxy(x_w[j], cur_y); cout << yum;
		}
		cur_y++;
	}

	_getch();
	delete[] x_w;
}

void studentCheckIn(Global &global) {
	//<View his attendance>
	system("CLS");
	cout << "ATTENDANCE : " << global.currentStudent.firstName << " " << global.currentStudent.lastName << endl;
	vector<Course> courseVec;
	global.courseStudentList.GetCoursesOfStudent(global.currentStudent.no,
		courseVec,
		global.courseList,
		global.stuList);
	if (courseVec.empty()) {
		cout << "You are not enrolled in any course." << endl;
		cout << "So, no attendance list." << endl;
		_getch();
		return;
	}

	//Choose a course
	//1,cs162,intro to prozip I(18ctt5),DBTien,
		    //08:30 - 11:30 at I44      13/3/2019 -> 16/3/2019
	int x_no = 0, x_ID = 5, x_name = 15, x_lec = 55, x_hour = 15, x_day = 55;
	int cur_y = WhereY();

	cout << endl;
	for (unsigned int i = 0; i < courseVec.size(); ++i) {
		gotoxy(x_no, cur_y); cout << i + 1;
		gotoxy(x_ID, cur_y); cout << courseVec[i].ID;
		gotoxy(x_name, cur_y); cout << courseVec[i].name;
		Lecturer lec; global.lecList.GetLecByNo(courseVec[i].lecturerNo, lec);
		gotoxy(x_lec, cur_y); cout << lec.firstName << " " << lec.lastName << endl;
		gotoxy(x_hour, cur_y + 1); cout << courseVec[i].startHour << " - " << courseVec[i].endHour << " at " << courseVec[i].room;
		gotoxy(x_day, cur_y + 1); cout << courseVec[i].startDate << " -> " << courseVec[i].endDate;
		cur_y += 2;
	}
	cout << endl << endl;
	int x;
	cout << "Choose a course (0 to return): "; cin >> x;
	if (x == 0 || x > (int)courseVec.size()) return;
	Course selectedCourse = courseVec[x - 1];

	int noWeek = selectedCourse.NumberOfWeek();

	system("CLS");
	cout << "Check-in for " << selectedCourse.ID << " - " << selectedCourse.name << endl;
	int *x_w = new int[noWeek + 1];
	x_w[1] = 0;
	for (int i = 2; i <= noWeek; ++i) x_w[i] = x_w[i - 1] + 4;
	cur_y = WhereY();

	for (int i = 1; i <= noWeek; ++i) {
		gotoxy(x_w[i], cur_y); cout << "W" << i;
	}
	cur_y++;

	for (int i = 1; i <= noWeek; ++i) {
		Attendance att;
		string yum = global.attendanceList.getAttendance(i,
			selectedCourse.no,
			global.currentStudent.no,
			att);
		gotoxy(x_w[i], cur_y); cout << yum;
	}
	cout << endl << endl;

	int cur_x = WhereX();
	cur_y = WhereY();
	do {
		gotoxy(cur_x, cur_y); cout << "                                                        ";
		gotoxy(cur_x, cur_y); cout << "Enter week number to check-in (0 to return): ";
		cin >> x;
		if (x<0 || x>noWeek) cout << "Please enter valid week number";
	} while (x<0 || x>noWeek);
	if (x == 0) return;

	global.attendanceList.addOrUpdateAttendance(x,
		selectedCourse.no,
		global.currentStudent.no,
		"P");

	//Show new attendance
	system("CLS");
	cout << "Check-in for " << selectedCourse.ID << " - " << selectedCourse.name << endl;
	cout << "P for Present, A for Absent" << endl;
	for (int i = 1; i <= noWeek; ++i) {
		gotoxy(x_w[i], cur_y); cout << "W" << i;
	}
	cur_y++;

	for (int i = 1; i <= noWeek; ++i) {
		Attendance att;
		string yum = global.attendanceList.getAttendance(i,
			selectedCourse.no,
			global.currentStudent.no,
			att);
		gotoxy(x_w[i], cur_y); cout << yum;
	}
	cout << endl << endl;
	cout << "Check-in complete." << endl;
	_getch();

	delete[] x_w;
}

/*
//BONUS SECTION, NOT FINISHED
void lecturerEditScreen(Global &global) {
	system("CLS");
	cout << "LECTURER EDIT" << endl;
	cout << "Press ESC to discard changes and return." << endl;
	string lecId;
	cout << "Enter lecturer accound: "; if (getlineESC(lecId)) return;
	
	Lecturer lec; 
	if (global.lecList.GetLecByID(lecId, lec)) {
		cout << "Enter first name: "; 
	}
	else {
		cout << "No such lecturer id exists." << endl;
		cout << "Please try again." << endl;
		_getch();
		return;
	}
}
//*/