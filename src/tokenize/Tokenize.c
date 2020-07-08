//
// Created by ivan on 08.07.2020.
//

#include "Tokenize.h"

void writeDataToFile(const wchar_t *data, int size, FILE *fptr) {
    wchar_t cur = 0;
    int isSpaceCur = 0;
    int isSpacePrev = 0;

    wchar_t* temp = malloc(sizeof(temp) * size);
    int idx = 0;

    for (int i = 0; i < size; i++) {
        cur = data[i];
        isSpaceCur = iswspace(cur);

        if (!(isSpaceCur || iswalpha(cur) || iswalnum(cur))) {
            continue;
        }

        if (!(isSpaceCur && isSpacePrev && cur != L'\n')) {
            temp[idx++] = cur;
        }

        isSpacePrev = isSpaceCur;
    }
    temp[idx] = '\0';
    fputws(temp, fptr);
    free(temp);
}

void cleanString(wchar_t *data, int size) {
    wchar_t c;
    for (int i = 0; i < size; i++) {
        c = data[i];
        if (!(iswalpha(c) || iswalnum(c) || iswspace(c))) {
            data[i] = L' ';
        }
    }
}

void tokenize(const char* inPath, const char* outPath) {
    FILE* inFile = fopen(inPath, "r");
    FILE* outFile = fopen(outPath, "w");

    int titleSymbols = 16 * KB;
    int textSymbols = 32 * MB;

    size_t titleSize = sizeof(wchar_t) * titleSymbols;
    size_t textSize = sizeof(wchar_t) * textSymbols;

    wchar_t* title = malloc(titleSize);
    wchar_t* text = malloc(textSize);

    memset(title, 0, titleSize);
    memset(text, 0, textSize);

    int documentIdx = 0;


    while (fgetws(title, titleSymbols, inFile) != NULL && fgetws(text, textSymbols, inFile)) {
        size_t currentTitleSize = wcslen(title);
        size_t currentTextSize = wcslen(text);
        cleanString(title, currentTitleSize);
        cleanString(text, currentTextSize);
        writeDataToFile(title, currentTitleSize, outFile);
        writeDataToFile(text, currentTextSize, outFile);
        if (++documentIdx % 5000 == 0) {
            printf("[Parsed] - %d\n", documentIdx);
        }
        wmemset(title, 0, currentTitleSize);
        wmemset(text, 0, currentTitleSize);
    }

    fclose(inFile);
    fclose(outFile);
}
