#include "ReadAll.hpp"
#include <sys/stat.h>
#include <cstdio>

bool ReadAll(const char *pathname, std::vector<uint8_t>& contents)
{
    struct stat st;
    bool ok;
    FILE *fp;

    if (stat(pathname, &st))
        return false;

    contents.resize(st.st_size);

    fp = fopen(pathname, "rb");
    if (!fp)
    {
        contents.clear();
        return false;
    }

    ok = contents.empty() || fread(&contents[0], contents.size(), 1, fp);
    fclose(fp);
    return ok;
}

#ifdef _WIN32
bool ReadAll(const wchar_t *pathname, std::vector<uint8_t>& contents)
{
    bool ok;
    FILE *fp;

#ifdef _MSC_VER
    struct _stat32 st;
    if (_wstat32(pathname, &st))
#else
    struct stat st;
    if (wstat(pathname, &st))
#endif
        return false;

    contents.resize(st.st_size);

    fp = _wfopen(pathname, L"rb");
    if (!fp)
    {
        contents.clear();
        return false;
    }

    ok = contents.empty() || fread(&contents[0], contents.size(), 1, fp);
    fclose(fp);
    return ok;
}
#endif

#ifdef UNITTEST
int main(int argc, char **argv)
{
    std::vector<uint8_t> data;
    if (ReadAll("ReadAll.cpp", data))
        fwrite(&data[0], data.size(), 1, stdout);
    return 0;
}
#endif
