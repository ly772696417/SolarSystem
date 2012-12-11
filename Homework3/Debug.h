#pragma once

#include <iostream>
#include <Windows.h>
#include <tchar.h>

class CDebug
{
private:
	FILE *m_pFile;
	static int m_Num;

public:
	CDebug(void);
	~CDebug(void);

	void LogMsg(char *lpszFormat,...);

	int getmNum();
};

