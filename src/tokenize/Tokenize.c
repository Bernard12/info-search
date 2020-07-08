//
// Created by ivan on 08.07.2020.
//

#include "Tokenize.h"

wchar_t convertToCorrectChar(wchar_t c) {
    if (iswalpha(c) || iswalnum(c) || iswspace(c)) {
        return c;
    }
    return L' ';
}

void writeDataToFile(wchar_t* data, int size, FILE* fptr) {
    wchar_t cur = 0, prev = 0;
    for (int i = 0; i < size; i++) {
        cur = data[i];

        if (!(iswspace(cur) || iswalpha(cur) || iswalnum(cur))) {
            continue;
        }

        if (!(iswspace(cur) && iswspace(prev))) {
            fwprintf(fptr, L"%lc", cur);
        }

        prev = cur;
    }
}

void tokenize(const char* inPath, const char* outPath) {
    FILE* inFile = fopen(inPath, "r");
    FILE* outFile = fopen(outPath, "w");

    size_t titleSize = sizeof(wchar_t) * 16 * KB;
    size_t textSize = sizeof(wchar_t) * 32 * MB;

    wchar_t* title = malloc(titleSize);
    wchar_t* text = malloc(textSize);

    memset(title, 0, titleSize);
    memset(text, 0, textSize);

    int documentIdx = 0;



    while (fgetws(title, titleSize, inFile) != NULL) {
        fgetws(text, textSize, inFile);
        size_t currentTitleSize = wcslen(title);
        size_t currentTextSize = wcslen(text);
        writeDataToFile(title, currentTitleSize, outFile);
        writeDataToFile(text, currentTextSize, outFile);
        if (++documentIdx % 100 == 0) {
            printf("[Parsed] - %d\n", documentIdx);
        }
    }

    fclose(inFile);
    fclose(outFile);
}
