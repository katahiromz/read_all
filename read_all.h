#pragma once

void *read_all(const char *pathname, size_t *psize);

#ifdef _WIN32
void *read_all_w(const wchar_t *pathname, size_t *psize);
#endif
