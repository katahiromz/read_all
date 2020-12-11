#pragma once

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif

LPVOID read_all_win32_a(LPCSTR pathname, SIZE_T *psize);
LPVOID read_all_win32_w(LPCWSTR pathname, SIZE_T *psize);

#ifdef UNICODE
    #define read_all_win32 read_all_win32_w
#else
    #define read_all_win32 read_all_win32_a
#endif
