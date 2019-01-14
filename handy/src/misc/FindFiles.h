/*
 *   Find and generate a file list of the folder.
**/

#ifndef FIND_FILES_H
#define FIND_FILES_H

#include <vector>
#include <string>

class FindFiles
{
public:
    FindFiles(){}
    ~FindFiles(){}

    std::vector<std::wstring> FindFiles::findFiles(const wchar_t *lpPath, const wchar_t *secName /*= ".*" */);

private:
    std::vector<std::wstring> file_lists;
};

#endif // FIND_FILES_H
