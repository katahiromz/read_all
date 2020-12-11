#include "read_all_win32.h"
#include <cstdio>

LPVOID read_all_win32_a(LPCSTR pathname, SIZE_T *psize)
{
    HANDLE hFile;
    DWORD dwSize, cbRead;
    LPVOID ptr;

    if (psize)
        *psize = 0;

    hFile = CreateFileA(pathname, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }

    dwSize = GetFileSize(hFile, NULL);
    if (dwSize == INVALID_FILE_SIZE)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    ptr = LocalAlloc(LMEM_FIXED, dwSize ? dwSize : 1);
    if (!ptr)
    {
        CloseHandle(hFile);
        return NULL;
    }

    if (ReadFile(hFile, ptr, dwSize, &cbRead, NULL) && dwSize == cbRead)
    {
        if (psize)
            *psize = dwSize;
    }
    else
    {
        LocalFree(ptr);
        ptr = NULL;
    }

    CloseHandle(hFile);
    return ptr;
}

LPVOID read_all_win32_w(LPCWSTR pathname, SIZE_T *psize)
{
    HANDLE hFile;
    DWORD dwSize, cbRead;
    LPVOID ptr;

    if (psize)
        *psize = 0;

    hFile = CreateFileW(pathname, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }

    dwSize = GetFileSize(hFile, NULL);
    if (dwSize == INVALID_FILE_SIZE)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    ptr = LocalAlloc(LMEM_FIXED, dwSize ? dwSize : 1);
    if (!ptr)
    {
        CloseHandle(hFile);
        return NULL;
    }

    if (ReadFile(hFile, ptr, dwSize, &cbRead, NULL) && dwSize == cbRead)
    {
        if (psize)
            *psize = dwSize;
    }
    else
    {
        LocalFree(ptr);
        ptr = NULL;
    }

    CloseHandle(hFile);
    return ptr;
}

#ifdef UNITTEST
int main(int argc, char **argv)
{
    LPVOID ptr;
    SIZE_T size;
    ptr = read_all_win32_a("read_all_win32.c", &size);
    if (ptr)
    {
        fwrite(ptr, size, 1, stdout);
        LocalFree(ptr);
    }
    return 0;
}
#endif
