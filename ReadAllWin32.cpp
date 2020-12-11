#include "ReadAllWin32.hpp"
#include <cstdio>

BOOL ReadAllWin32A(LPCSTR pathname, std::vector<BYTE>& contents)
{
    HANDLE hFile;
    DWORD dwSize, cbRead;
    BOOL bOK;

    hFile = CreateFileA(pathname, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        contents.clear();
        return FALSE;
    }

    dwSize = GetFileSize(hFile, NULL);
    if (dwSize == INVALID_FILE_SIZE)
    {
        CloseHandle(hFile);
        contents.clear();
        return FALSE;
    }
    contents.resize(dwSize);

    bOK = contents.empty() || (ReadFile(hFile, &contents[0], dwSize, &cbRead, NULL) && dwSize == cbRead);

    CloseHandle(hFile);
    return bOK;
}

BOOL ReadAllWin32W(LPCWSTR pathname, std::vector<BYTE>& contents)
{
    HANDLE hFile;
    DWORD dwSize, cbRead;
    BOOL bOK;

    hFile = CreateFileW(pathname, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        contents.clear();
        return FALSE;
    }

    dwSize = GetFileSize(hFile, NULL);
    if (dwSize == INVALID_FILE_SIZE)
    {
        CloseHandle(hFile);
        contents.clear();
        return FALSE;
    }
    contents.resize(dwSize);

    bOK = contents.empty() || (ReadFile(hFile, &contents[0], dwSize, &cbRead, NULL) && dwSize == cbRead);

    CloseHandle(hFile);
    return bOK;
}

#ifdef UNITTEST
int main(int argc, char **argv)
{
    std::vector<BYTE> data;
    if (ReadAllWin32A("ReadAllWin32.cpp", data))
        fwrite(&data[0], data.size(), 1, stdout);
    return 0;
}
#endif
