#include <cstdlib>
#include <cstring>

char* concat(const char* fst, const char* snd) {
    char* result = (char*) malloc(strlen(fst) + strlen(snd) + 1);
    if (!result) return nullptr;

    int i = 0;
    while (fst[i] != '\0') {
        result[i] = fst[i];
        i++;
    }

    int j = 0;
    while (snd[j] != '\0') {
        result[i] = snd[j];
        i++;
        j++;
    }

    result[i] = '\0';

    return result;
}