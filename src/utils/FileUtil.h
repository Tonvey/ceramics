#pragma once
#include <string>

class FileUtil
{
public:
    static const char pathChar;
    static std::string getFileDirName(std::string file);
    static bool getFileContent(const std::string fileName,std::string &outContent);
};
