// Profile.h: interface for the CProfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFILE_H__2FF6A18E_3F01_4357_960E_D48381DFE0D9__INCLUDED_)
#define AFX_PROFILE_H__2FF6A18E_3F01_4357_960E_D48381DFE0D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_LEN        1000


class CProfile  
{
public:
	CProfile();
	virtual ~CProfile();

public:
	static BOOL WriteProfileString(const CString strSection, const CString strEntry,
		const CString strValue, const CString strIniPath);

	static CString GetProfileString(const CString strSection, const CString strEntry,
		const CString strDefault, const CString strIniPath);

	static BOOL WriteProfileInt(const CString strSection, const CString strEntry, 
		const int iValue, const CString strIniPath);

	static int GetProfileInt(const CString strSection, const CString strEntry,
		const int iDefault, const CString strIniPath);


	static DWORD GetPrivateProfileString_RDEF(   
		LPCTSTR lpAppName,   
		LPCTSTR lpKeyName, 
		LPCTSTR lpDefault, 
		LPTSTR lpReturnedString,   
		DWORD nSize,   
		LPCTSTR lpFileName
		) ;

	
	static int id;
	static CString name;
};

#endif // !defined(AFX_PROFILE_H__2FF6A18E_3F01_4357_960E_D48381DFE0D9__INCLUDED_)

