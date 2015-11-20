#include "stdafx.h"
#include <Windows.h>
#include "Select_template.h"

using namespace std;
using namespace Select_File;

unsigned Select_File::selFile( string &strFile,const string &strExt,bool bOpen )
{
    string strDir = "D:\\Downloads";//����ͨ��strFile����Ŀ¼,CFileDialog���Զ���ס
    string filename = "hi.txt";  //ͨ��strFile�����ļ���
    string filter = strExt + "�ļ� (*." + strExt + ")|*." + strExt + "||";
    string ext = "." + strExt;

    CFileDialog dlg(bOpen,ext.c_str(),filename.c_str(),OFN_READONLY|OFN_OVERWRITEPROMPT,filter.c_str(),NULL);
    dlg.GetOFN().lpstrInitialDir = strFile.c_str();// Ĭ��Ŀ¼

    if (dlg.DoModal())
    {
        strFile = dlg.GetPathName();
        return IDOK;
    }

    return IDCANCEL;
}

int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
    switch(uMsg)
    {
    case BFFM_INITIALIZED:
        ::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData);
        break;
    }

    return 0;
}

unsigned Select_File::selDir( string &strDir,void *hwnd/* = NULL*/ )
{
    char szDir[MAX_PATH];
    BROWSEINFO bi; 
    bi.hwndOwner = (HWND)hwnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szDir;
    bi.lpszTitle = "ѡ��λ�ã�";
    bi.iImage = 0;

    bi.ulFlags = BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
    bi.lpfn = BrowseCallbackProc;
    bi.lParam = (LPARAM)(LPCTSTR)strDir.c_str();

    LPITEMIDLIST lp = SHBrowseForFolder(&bi);
    if (lp && SHGetPathFromIDList(lp,szDir))
    {
        strDir = szDir;
        return IDOK;
    }

    return IDCANCEL;
}