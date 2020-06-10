#pragma once

#define    INIFILELPATH				TEXT("setting.ini") //配置文件路径

class CIniFile
{
public:
	CIniFile(void);
	~CIniFile(void);
	
	// 写INI文件
	static void WriteIniFile(const TCHAR* lpSection,const TCHAR* lpKey,const TCHAR* lpValue);	
	// 读INI文件,返回INT
	static int  GetIniFileInt(const TCHAR* lpSection,const TCHAR* lpKey);	
	// 读INI文件，返回字符串
	static CString GetIniFileString(const TCHAR* lpSection,const TCHAR* lpKey);	
	// 读配置INI文件路径
	static CString GetCurrentApPath();	
};

