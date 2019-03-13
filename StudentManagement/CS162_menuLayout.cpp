void startScreen()
{
	cout << "  _________    __      __    _________  " << endl;
	cout << " |   ______|  |  \\    /  |  |   ______| " << endl;
	cout << " |  |         |   \\  /   |  |  |         " << endl;
	cout << " |  |______   |    \\/    |  |  |______     " << endl;
	cout << " |______   |  |  |\\__/|  |  |______   |    " << endl;
	cout << "        |  |  |  |    |  |         |  |   " << endl;
	cout << "  ______|  |  |  |    |  |   ______|  |    " << endl;
	cout << " |_________|  |__|    |__|  |_________|    " << endl;
	cout << "____________________________________________ " << endl;
	cout << endl << " Student Management System" << endl;
	cout << " By Group []" << endl << endl;//quen nhom may roi
	for (int i = 1; i <= 15; ++i)
	{
		cout << "/_\\";
		Sleep(160);
	}
	cout << "  Please press enter to get start!";
	cin.get();
	system("CLS");
}

void startMenu()
{
	cout << "  _______" << endl;
	cout << " /       \\" << endl;
	cout << "|  Login  |" << endl;
	cout << " \\_______/" << endl;
	cout << "  _______" << endl;
	cout << " /       \\" << endl;
	cout << "|  Exit   |" << endl;
	cout << " \\_______/" << endl;
}