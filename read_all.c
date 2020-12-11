#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "read_all.h"

void *read_all(const char *pathname, size_t *psize)
{
    struct stat st;
    size_t size;
    int ok;
    void *ptr;
    FILE *fp;

    if (psize)
        *psize = 0;

    if (stat(pathname, &st))
        return NULL;

    size = st.st_size;
    ptr = malloc(size ? size : 1);
    if (!ptr)
        return NULL;

    fp = fopen(pathname, "rb");
    if (!fp)
    {
        free(ptr);
        return NULL;
    }

    ok = !size || fread(ptr, size, 1, fp);
    fclose(fp);

    if (ok)
    {
        if (psize)
            *psize = size;
        return ptr;
    }

    free(ptr);
    return NULL;
}

#ifdef _WIN32
void *read_all_w(const wchar_t *pathname, size_t *psize)
{
    struct stat st;
    size_t size;
    int ok;
    void *ptr;
    FILE *fp;

    if (psize)
        *psize = 0;

    if (wstat(pathname, &st))
        return NULL;

    size = st.st_size;
    ptr = malloc(size ? size : 1);
    if (!ptr)
        return NULL;

    fp = _wfopen(pathname, L"rb");
    if (!fp)
    {
        free(ptr);
        return NULL;
    }

    ok = !size || fread(ptr, size, 1, fp);
    fclose(fp);

    if (ok)
    {
        if (psize)
            *psize = size;
        return ptr;
    }

    free(ptr);
    return NULL;
}
#endif

#ifdef UNITTEST
int main(void)
{
    size_t size;
    void *ptr = read_all("read_all.c", &size);
    fwrite(ptr, size, 1, stdout);
    free(ptr);
    return 0;
}
#endif
