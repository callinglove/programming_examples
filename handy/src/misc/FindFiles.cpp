#include "stdafx.h"
#include "FindFiles.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>  
#include <stdio.h> 

#ifdef WIN32

#include <Windows.h>
#include <direct.h>

std::vector<std::wstring> FindFiles::findFiles( const wchar_t *lpPath, const wchar_t *secName /*= ".*" */ )
{
    wchar_t szFind[MAX_PATH];
    wchar_t szFile[MAX_PATH];

    WIN32_FIND_DATA FindFileData;

    wcscpy(szFind,lpPath);
    wcscat(szFind,L"\\*");
    //wcscat(szFind,secName);

    HANDLE hFind=::FindFirstFile(szFind,&FindFileData);

    if(INVALID_HANDLE_VALUE == hFind)
    {
        std::cout << "Empty folder!" << std::endl;
        return std::vector<std::wstring>();
    }

    do
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(FindFileData.cFileName[0]!='.')
            {
                wcscpy(szFile,lpPath);
                wcscat(szFile,L"\\");
                wcscat(szFile,FindFileData.cFileName);
                findFiles(szFile, secName);
            }
        }
        else
        {
            if ( szFile[0] )
            {
                std::wstring filePath(lpPath);
                filePath += L"\\";
                filePath += FindFileData.cFileName;
                
                file_lists.push_back(filePath);
            }
            else
            {
                std::wstring filePath = szFile;
                filePath += FindFileData.cFileName;
                file_lists.push_back(filePath);
            }
        }

    }while(::FindNextFile(hFind,&FindFileData));

    ::FindClose(hFind);
    return file_lists;
}

#else

#include <dirent.h>
#include <string.h>
#include <queue>

std::vector<std::string> FindFiles::findFiles( const wchar_t *lpPath, const wchar_t *secName /*= ".*" */ )
{
    (void)secName;

    std::vector<std::string> result;
    std::queue<std::string> queue;
    std::string dirname;

    DIR *dir;
    if ( !(dir = opendir ( lpPath )) ) {
        return result;
    }
    queue.push( lpPath );

    struct dirent *ent;
    while ( !queue.empty() )
    {

        dirname = queue.front();
        dir = opendir( dirname.c_str() );
        queue.pop();
        if ( !dir ) { continue; }

        while( ent = readdir( dir ) )
        {

            if ( strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0 )
            {
                continue;
            }
            if ( ent->d_type == DT_DIR )
            {
                queue.push( dirname+"/"+ent->d_name );
            }
            else
            {
                result.push_back( dirname+"/"+ent->d_name );
            }

        }

        closedir( dir );

    }

    return result;
}

#endif
