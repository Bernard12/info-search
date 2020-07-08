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
        if (!(iswspace(cur) && iswspace(prev))) {
            fwprintf(fptr, L"%lc", cur);
        }
        prev = cur;
    }
    fwprintf(fptr, L"\n");
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

    int currentMode = READ_TITLE;
    int titleIdx = 0;
    int textIdx = 0;
    int documentIdx = 0;

    wchar_t c;
    while ((c = fgetwc(inFile)) != WEOF) {
        if (c == L'\n') {
            currentMode++;
            if (currentMode == WRITE_OUTPUT) {
                writeDataToFile(title, titleIdx, outFile);
                writeDataToFile(text, textIdx, outFile);
                memset(title, 0, titleSize);
                memset(text, 0, textSize);
                titleIdx = textIdx = 0;
                currentMode = READ_TITLE;
                documentIdx++;
                if (documentIdx % 100 == 0) {
                    printf("[PARSED]- %d\n", documentIdx);
                }
            }
            continue;
        }

        c = convertToCorrectChar(c);

        if (currentMode == READ_TITLE) {
            title[titleIdx++] = c;
        } else if (currentMode == READ_TEXT) {
            text[textIdx++] = c;
        }
    }
    fclose(inFile);
    fclose(outFile);
}
