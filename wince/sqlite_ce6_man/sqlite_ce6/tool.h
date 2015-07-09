
#if !defined( AFX_TOOL_H_BA3CD1E5_8B22_4164_9091_97100F18C380__INCLUDED_)
#define AFX_TOOL_H_BA3CD1E5_8B22_4164_9091_97100F18C380__INCLUDED_

	CString GetInIFileName();

	BOOL WritestrToInI(CString pare_node,CString child_node,CString strvalue);
	CString  ReadstrFromInI(CString pare_node,CString child_node,CString default_value);
	BOOL WriteIntFromInI(const CString strSection, const CString strEntry,const int iDefault);
	UINT32 ReadIntFromInI(const CString strSection, const CString strEntry,const int iDefault);
	
	//char* GetLogFileName();
	void GetCurrentDirectory(CString &strPath);
	void SaveLog(char *buf,UINT16 len);
	void SaveLog_L(char *buf);
	void SaveLog_Hex(char *buf,UINT16 len);
	void SaveLog_Hex(UINT8 *buf,UINT16 len);
	void ANSITOUTF8(char* szAnsi);
	void UTF8TOANSI(char* szutf8);

#define SETFONT(font,height) { if(font.m_hObject) font.DeleteObject();\
	LPCTSTR ftName = _T("ËÎÌו");\
	if (!font.CreateFont(height,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,\
	CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_ROMAN,ftName));}
#endif