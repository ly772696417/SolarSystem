#pragma once

#include <iostream>
#include <Windows.h>
#include <tchar.h>

class Debug
{
private:
	FILE *m_pFile;
	static int m_Num;

public:
	Debug(void);
	~Debug(void);

	void LogMsg(char *lpszFormat,...);

	int getmNum();
};

