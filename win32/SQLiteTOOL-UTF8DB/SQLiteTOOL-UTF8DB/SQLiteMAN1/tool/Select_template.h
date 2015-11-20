#include <string>

using namespace std;
namespace Select_File
{
    // 选择文件，可设置定位到默认目录
    unsigned selFile(string &strFile,const string &strExt,bool bOpen);

    // 选择目录，可设置定位初始目录
    unsigned selDir(string &strDir,void *hwnd = NULL);
}