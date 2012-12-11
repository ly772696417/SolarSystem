#include "Debug.h"

int CDebug::m_Num = 0;

CDebug::CDebug(void)
{
	if (!m_Num)
	{
		m_pFile = NULL;
		m_pFile = fopen("Log.txt","wb");
		fclose(m_pFile);
	}

	m_Num++;
}


CDebug::~CDebug(void)
{
	m_Num--;
}


void CDebug::LogMsg(char * lpszFormat,...){
	va_list pArgList;

	va_start(pArgList,lpszFormat);
	m_pFile = fopen("log.txt","a+");
	if (m_pFile != NULL)	
	{
		vfprintf(m_pFile,lpszFormat,pArgList);
		fprintf(m_pFile,"\n");
		fclose(m_pFile);
	}
	va_end(pArgList);
}


int CDebug::getmNum(){
	return m_Num;
}