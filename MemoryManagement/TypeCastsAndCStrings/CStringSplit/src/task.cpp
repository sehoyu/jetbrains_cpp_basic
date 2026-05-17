#include <cstdlib>
#include <cstring>

size_t split(const char* str, const char* seps, char**& res) {
    // 1. str을 순회하면서 단어 개수 파악
    size_t strLen = strlen(str);
    size_t sepsLen = strlen(seps);

    if (strLen == 0) {
        res = nullptr;
        return 0;
    }

    int count = 0;
    bool prevSep = false;
    for (int i = 0; i <= strLen; i++) {
        bool curSep = false;
        for (int j = 0; j < sepsLen; j++) {
            if (str[i] == seps[j]) {
                curSep = true;
            }
        }

        if (curSep || str[i] == '\0') {
            if (!prevSep && i != 0) {
                count++;
            }
            prevSep = true;
            continue;
        }

        prevSep = false;
    }

    // 2. 단어 개수로 res 배열 공간 할당
    if (count == 0) {
        res = nullptr;
        return 0;
    }

    res = (char**) malloc(sizeof(char*) * count);

    int row = 0;
    int col = 0;
    prevSep = false;
    for (int i = 0; i <= strLen; i++) {
        bool curSep = false;
        for (int j = 0; j < sepsLen; j++) {
            if (str[i] == seps[j]) {
                curSep = true;
            }
        }

        if (curSep || str[i] == '\0') {
            if (!prevSep && i != 0) {
                res[row] = (char*) malloc(col + 1);
                res[row][col] = '\0';
                row++;
            }

            col = 0;
            prevSep = true;
            continue;
        }

        col++;
        prevSep = false;
    }

    // 3. 파악한 정보로 res 배열에 str 단어들을 복사(할당)
    row = 0;
    col = 0;
    prevSep = false;
    for (int i = 0; i <= strLen; i++) {
        bool curSep = false;
        for (int j = 0; j < sepsLen; j++) {
            if (str[i] == seps[j]) {
                curSep = true;
            }
        }

        if (curSep || str[i] == '\0') {
            if (!prevSep && i != 0) {
                row++;
            }

            col = 0;
            prevSep = true;
            continue;
        }

        res[row][col] = str[i];
        col++;
        prevSep = false;
    }

    return count;
}