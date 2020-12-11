#pragma once

#include <vector>
#include <cstdint>

bool ReadAll(const char *pathname, std::vector<uint8_t>& contents);

#ifdef _WIN32
    bool ReadAll(const wchar_t *pathname, std::vector<uint8_t>& contents);
#endif
