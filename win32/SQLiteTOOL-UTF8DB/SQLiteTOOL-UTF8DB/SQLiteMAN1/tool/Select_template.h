#include <string>

using namespace std;
namespace Select_File
{
    // ѡ���ļ��������ö�λ��Ĭ��Ŀ¼
    unsigned selFile(string &strFile,const string &strExt,bool bOpen);

    // ѡ��Ŀ¼�������ö�λ��ʼĿ¼
    unsigned selDir(string &strDir,void *hwnd = NULL);
}