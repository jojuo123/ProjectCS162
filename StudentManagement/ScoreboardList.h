#pragma once
#ifndef _ScoreboardList_h_
#define _ScoreboardList_h_
#include "Scoreboard.h"
#include "StudentList.h"

struct ScoreboardList
{
	vector<Scoreboard> Scorelist;

	bool ImportFromfile(string filename);
	bool SaveToFile(string filename);
	bool AddOrUpdate(Scoreboard &sc);
	Scoreboard GetScoreboard(int stuno, int courseno);
	bool ExportCsv(int courseno,string filename);
	bool ImportFromCSV(string filename, int courseNo, StudentList &stuList);
};

#endif // !_
