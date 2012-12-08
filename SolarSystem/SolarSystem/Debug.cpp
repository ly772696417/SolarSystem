#include "Debug.h"

int Debug::m_Num = 0;

Debug::Debug(void)
{
	if (!m_Num)
	{
		m_pFile = NULL;
		m_pFile = fopen("Log.txt","wb");
		fclose(m_pFile);
	}

	m_Num++;
}


Debug::~Debug(void)
{
	m_Num--;
}


void Debug::LogMsg(char * lpszFormat,...){
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


int Debug::getmNum(){
	return m_Num;
}