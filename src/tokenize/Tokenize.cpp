//
// Created by ivan on 08.07.2020.
//

#include "Tokenize.h"

wchar_t temp[1024 * 1024] = {0};

void writeDataToFile(const wchar_t *data, int size, std::wofstream& out) {
    wchar_t cur = 0;
    int isSpaceCur = 0;
    int isSpacePrev = 0;

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
    temp[idx] = 0;
    out << temp << L'\n';
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
    std::wifstream in(inPath);
    std::wofstream out(outPath);

    int titleSymbols = 16 * KB;
    int textSymbols = 32 * MB;

    size_t titleSize = sizeof(wchar_t) * titleSymbols;
    size_t textSize = sizeof(wchar_t) * textSymbols;

    auto* title = new wchar_t[titleSize];
    auto* text = new wchar_t[textSize];

    memset(title, 0, titleSize);
    memset(text, 0, textSize);

    int documentIdx = 0;

    while (in.getline(title, titleSymbols, L'\n') && in.getline(text, textSymbols, L'\n')) {
        size_t currentTitleSize = wcslen(title);
        size_t currentTextSize = wcslen(text);
        out << title << L'\n';
        cleanString(title, currentTitleSize);
        cleanString(text, currentTextSize);
        writeDataToFile(title, currentTitleSize, out);
        writeDataToFile(text, currentTextSize, out);
        if (++documentIdx % 5000 == 0) {
            printf("[Parsed] - %d\n", documentIdx++);
        }
    }

    in.close();
    out.close();
    delete[] title;
    delete[] text;
}
