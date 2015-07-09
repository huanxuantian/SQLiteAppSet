// Profile.cpp: implementation of the CProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Profile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int CProfile::id = 1;
CString CProfile::name = L"list";

CProfile::CProfile()
{

}

CProfile::~CProfile()
{

}

DWORD GetPrivateProfileString_RDEF(   
LPCTSTR lpAppName,   
LPCTSTR lpKeyName, 
LPCTSTR lpDefault, 
LPTSTR lpReturnedString,   
DWORD nSize,   
LPCTSTR lpFileName   
) 
{ 
    CFile iniFile;   
    PBYTE pFileBuf;  
    CString szBuf; 
    DWORD dwLength; 

    if (lpFileName == NULL || lpReturnedString == NULL) 
        return 0; 

    *lpReturnedString = TCHAR('\0'); 
    nSize = 0;   

    if(!iniFile.Open(lpFileName, CFile::modeRead))   
        return 0;   

    dwLength = (DWORD)iniFile.GetLength(); 
if (dwLength == 0) 
        return 0;   
    pFileBuf = new BYTE[dwLength + 2];   
    if (pFileBuf == NULL)   
        return 0; 
    memset(pFileBuf, 0x0, dwLength + 2); 
    iniFile.Read((void *)pFileBuf, dwLength); 
iniFile.Close();   

    if (pFileBuf[0] == 0xFF && pFileBuf[1] == 0xFE) 
        szBuf = (LPCWSTR)(pFileBuf + 2); 
    else 
    { 
        PTCHAR pszWideChar = new TCHAR[dwLength + 1]; 
        MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pFileBuf, dwLength, pszWideChar, dwLength); 
        szBuf = pszWideChar; 
        delete pszWideChar; 
    }   
    delete pFileBuf; 

    while (1) 
    { 
        CString szTemp;   
        int nPos; 
        if (szBuf.IsEmpty()) 
            goto _GetPrivateProfileString_EXIT;
        nPos = szBuf.FindOneOf(TEXT("\r\n"));   
        if (nPos == -1) 
        {   
            szTemp = szBuf;
            szBuf.Empty();   
        } 
        else   
        { 
            szTemp = szBuf.Left(nPos); 
            szBuf = szBuf.Right(szBuf.GetLength() - nPos);   
            szBuf.TrimLeft(TEXT("\r\n")); 
        }   

        szTemp.TrimLeft(TEXT("\t ")); 
        szTemp.TrimRight(TEXT("\t "));   
        if (szTemp.GetAt(0) == TEXT('[') && 
            szTemp.GetAt(szTemp.GetLength() - 1) == TEXT(']')) 
        { 
            szTemp = szTemp.Right(szTemp.GetLength() - 1); 
            szTemp = szTemp.Left(szTemp.GetLength() - 1); 
            if (lpAppName == NULL)  
            { 
                memcpy(lpReturnedString + nSize, (LPCTSTR)szTemp, (szTemp.GetLength() + 1)* sizeof(TCHAR)); 
                nSize += szTemp.GetLength() + 1;  
            } 
            else if (szTemp.Compare(lpAppName) == 0) 
            { 
                while (1)  
                {   
                    if (szBuf.IsEmpty()) 
                        goto _GetPrivateProfileString_EXIT;   

                    nPos = szBuf.FindOneOf(TEXT("\r\n")); 
                    if (nPos == -1) 
{ 
                        szTemp = szBuf; 
                        szBuf.Empty(); 
                    } 
                    else
                    { 
                        szTemp = szBuf.Left(nPos); 
                        szBuf = szBuf.Right(szBuf.GetLength() - nPos); 
                        szBuf.TrimLeft(TEXT("\r\n")); 
                    } 

                    nPos = szTemp.Find(TEXT("=")); 
                    if (nPos == -1) 
                        goto _GetPrivateProfileString_EXIT; 
                    CString szTemp1;   
                    szTemp1 = szTemp.Left(nPos); 
                    szTemp1.TrimLeft(TEXT("\t "));
                    szTemp1.TrimRight(TEXT("\t ")); 
                    if (lpKeyName == NULL) 
                    { 
                        memcpy(lpReturnedString + nSize, (LPCTSTR)szTemp1, (szTemp1.GetLength() + 1)* sizeof(TCHAR)); 
                        nSize += szTemp1.GetLength() + 1;   
                    } 
                    else if (szTemp1.Compare(lpKeyName) == 0) 
                    { 
                        szTemp1 = szTemp.Right(szTemp.GetLength() - nPos - 1); 
                        szTemp1.TrimLeft(TEXT("\t ")); 
                        szTemp1.TrimRight(TEXT("\t ")); 
                        memcpy(lpReturnedString + nSize, (LPCTSTR)szTemp1, (szTemp1.GetLength() + 1)* sizeof(TCHAR)); 
                        nSize += szTemp1.GetLength() + 1; 
                        goto _GetPrivateProfileString_EXIT;   
                    }
                } 
            }   
        } 
    } 

_GetPrivateProfileString_EXIT: 
    lpReturnedString[nSize] = TEXT('\0'); 
    return nSize;
}





BOOL CProfile::WriteProfileString(const CString strSection, const CString strEntry, const CString strValue, const CString strIniPath)
{
    if(strSection == L"" || strEntry == L"" || strValue == L"" || strIniPath == L"")
    {
        return FALSE;
    }
    CFile IniFile;
    CString strCombine;
    
    TRY
    {
        if(! IniFile.Open(strIniPath, CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate))
        {
            return FALSE;
        }
        
        if(IniFile.GetLength() == 0)
        {
            strCombine = L"[" + strSection + L"]" + L"\r\n"
                + strEntry + L"=" + strValue + L"\r\n";
            LPTSTR lpCombine = strCombine.GetBuffer(0);
            IniFile.Write(lpCombine, strCombine.GetLength() * 2);
            IniFile.Close();
            return TRUE;
        }
        
        WCHAR *pBuf;
        pBuf = new WCHAR[(unsigned int)IniFile.GetLength() / 2 + 1];
        if(pBuf == NULL)
        {
            IniFile.Close();
            return FALSE;
        }
        if(IniFile.Read(pBuf, (UINT)IniFile.GetLength()) != IniFile.GetLength())
        {
            delete[] pBuf;
            IniFile.Close();
            return FALSE;
        }
        
        pBuf[IniFile.GetLength() / 2] = NULL;
        strCombine.GetBuffer(MAX_LEN);
        strCombine = pBuf;
        delete[] pBuf;
        
        int iIndex1, iIndex2, iIndex3, iIndexT;
        iIndex1 = strCombine.Find(L"[" + strSection + L"]\r\n");
        if(iIndex1 == -1)
        {
            strCombine += L"[" + strSection + L"]" + L"\r\n"
                + strEntry + L"=" + strValue + L"\r\n";
            
            LPTSTR lpCombine = strCombine.GetBuffer(0);
            IniFile.SetLength(0);
            IniFile.SeekToBegin();
            IniFile.Write(lpCombine, strCombine.GetLength() * 2);
            IniFile.Close();
            return TRUE;
        }
        //iIndexT = iIndex1 + 4 + strSection.GetLength();
		iIndexT = iIndex1 + strSection.GetLength() + 2; //2代表"[]"两个字符
        iIndex2 = strCombine.Find(strEntry + L"=", iIndexT);
        if(iIndex2 == -1)
        {
            strCombine.Insert(iIndexT, L"\r\n" + strEntry + L"=" + strValue/* + L"\r\n"*/);
            
            LPTSTR lpCombine = strCombine.GetBuffer(0);
            IniFile.SetLength(0);
            IniFile.SeekToBegin();
            IniFile.Write(lpCombine, strCombine.GetLength() * 2);
            IniFile.Close();
            return TRUE;
        }
        else
        {
            iIndex3 = strCombine.Find(L"\r\n", iIndex2 + 1);
            if(iIndex3 == -1)
            {
                IniFile.Close();
                return FALSE;
            }
            iIndexT = iIndex2 + 1 + strEntry.GetLength();
            strCombine.Delete(iIndexT, iIndex3 - iIndexT);
            strCombine.Insert(iIndexT, strValue);
            
            LPTSTR lpCombine = strCombine.GetBuffer(0);
            IniFile.SetLength(0);
            IniFile.SeekToBegin();
            IniFile.Write(lpCombine, strCombine.GetLength() * 2);
            IniFile.Close();
            return TRUE;
        }
        
    }
    CATCH(CFileException, e)
    {
    }
    END_CATCH
        
        IniFile.Close();
    return FALSE;
}

CString CProfile::GetProfileString(const CString strSection, const CString strEntry, const CString strDefault, const CString strIniPath)
{
    if(strSection == L"" || strEntry == L"" || strIniPath == L"")
    {
        return strDefault;
    }
    CFile IniFile;
    CString strCombine;
    
    TRY
    {
        if(! IniFile.Open(strIniPath, CFile::modeRead))
        {
            return strDefault;
        }
		
        if(IniFile.GetLength() == 0)
        {
            IniFile.Close();
            return strDefault;
        }
	

        WCHAR *pBuf;
        pBuf = new WCHAR[(unsigned int)IniFile.GetLength() / 2 + 1];
        if(pBuf == NULL)
        {
            IniFile.Close();
            return strDefault;
        }
	

        if(IniFile.Read(pBuf,(UINT) IniFile.GetLength()) != IniFile.GetLength())
        {
            delete[] pBuf;
            IniFile.Close();
            return strDefault;
        }

	

        pBuf[IniFile.GetLength() / 2] = NULL;
        strCombine.GetBuffer(MAX_LEN);
        strCombine = pBuf;
        delete[] pBuf;
        
        int iIndex1, iIndex2, iIndex3, iIndexT;
        iIndex1 = strCombine.Find(L"[" + strSection + L"]\r\n");
        if(iIndex1 == -1)
        {
            IniFile.Close();
            return strDefault;
        }

        iIndexT = iIndex1 + strSection.GetLength() + 2; //2代表"[]"两个字符

		iIndex2 = strCombine.Find(strEntry + L"=" ,iIndexT);
			
        if(iIndex2 == -1)
        {

            IniFile.Close();
            return strDefault;
        }
        else
        {

            iIndex3 = strCombine.Find(L"\r\n", iIndex2 + 1);
            if(iIndex3 == -1)
            {
                IniFile.Close();
                return strDefault;
            }

            iIndexT = iIndex2 + 1 + strEntry.GetLength(); //这里1代表'='的长度
            IniFile.Close();
            return strCombine.Mid(iIndexT, iIndex3 - iIndexT);
        }
    }
    CATCH(CFileException, e)
    {
    }
    END_CATCH
        
        IniFile.Close();
    return strDefault;
}

BOOL CProfile::WriteProfileInt(const CString strSection, const CString strEntry, const int iValue, const CString strIniPath)
{
	wchar_t cBuff[MAX_LEN];
	CString strValue("");
	
	_itow(iValue, cBuff, 10);
	strValue.Format(_T("%s"), cBuff);
	
	return CProfile::WriteProfileString(strSection, strEntry, strValue, strIniPath);
}


int CProfile::GetProfileInt(const CString strSection, const CString strEntry, const int iDefault, const CString strIniPath)
{
	wchar_t cBuff[MAX_LEN];
	CString strDefault("");
	CString strReturn("");
	
	_itow(iDefault, cBuff, 10);
	strDefault.Format(_T("%s"), cBuff);
	
	strReturn = CProfile::GetProfileString(strSection, strEntry, strDefault, strIniPath);
	
	return (_ttoi(strReturn));
}