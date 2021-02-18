#include "FileUtil.h"
#include <fstream>
#include <iostream>
using namespace std;

#ifdef _WIN32
#define PATH_CHAR '\\'
#else
#define PATH_CHAR '/'
#endif

const char FileUtil::pathChar = PATH_CHAR;

string FileUtil::getFileDirName(string file)
{
    auto pos = file.rfind(PATH_CHAR);
    string curPath = file.substr(0,pos);
    return curPath;
}
bool FileUtil::getFileContent(const std::string fileName,std::string &outContent)
{
    string content ;
    ifstream stream(fileName,std::ios::in);
    if(stream.is_open())
    {
        char buf[1024];
        memset(buf,0,sizeof(buf));
        while(!stream.eof())
        {
            stream.read(buf,sizeof(buf)-1);
            content.append(buf,stream.gcount());
        }
        stream.close();
    }
    else
    {
        cerr<<"Can not open shader file "<<endl;
        return false;
    }
    outContent = content;
    return true;
}
