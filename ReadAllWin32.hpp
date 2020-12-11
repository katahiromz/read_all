#pragma once

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif
#include <vector>

BOOL ReadAllWin32A(LPCSTR pathname, std::vector<BYTE>& contents);
BOOL ReadAllWin32W(LPCWSTR pathname, std::vector<BYTE>& contents);

#ifdef UNICODE
    #define ReadAllWin32 ReadAllWin32W
#else
    #define ReadAllWin32 ReadAllWin32A
#endif
