#include <iostream>
#include <vector>
#include "..\..\iniFile\IniFile.h"

using namespace std;

int main(void)
{
    CIniFile iniFile;
	iniFile.Create("test.ini");

	int iPeopleNum;
	iniFile.GetVarInt("Config", "Number Of People", iPeopleNum);

	vector<CString> vPeoples;
	for (int iPeople = 0; iPeople < iPeopleNum; ++iPeople)
	{
		CString csPeopleKey, csPeopleName;
		csPeopleKey.Format("People%d", iPeople);
		iniFile.GetVarStr("Config", csPeopleKey, csPeopleName);
		vPeoples.push_back(csPeopleName);
	}

	cout << "The world have " << iPeopleNum << " kinds of people" << endl;
	for (int iPeople = 0; iPeople < iPeopleNum; ++iPeople)
	{
		cout << iPeople << ":" <<vPeoples[iPeople] << endl;
	}
	system("pause");
    return 0;
}