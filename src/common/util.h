#ifndef RTR_COLLECTION_UTIL_H
#define RTR_COLLECTION_UTIL_H

#include <iostream>

inline char *loadFile(const char *filename)
{
    FILE *f = fopen(filename, "r");

    if (!f)
        return NULL;

    fseek(f, 0, SEEK_END);
    const size_t len = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);

    char *str = (char *) malloc((len + 1) * sizeof(char));

    if (!str)
    {
        fclose(f);
        return NULL;
    }

    size_t read = 0;
    if (len > 0)
        read = fread(str, sizeof(char), len, f);

    str[read] = '\0';

    fclose(f);

    return str;
}

#endif //RTR_COLLECTION_UTIL_H
