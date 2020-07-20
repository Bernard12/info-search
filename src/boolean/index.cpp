//
// Created by ivan on 10.07.2020.
//

#include "index.h"

// for doc list


int getRealEnd(const wchar_t *str) {
    int size = wcslen(str);
    int res = size - 1;
    while (str[res] == L' ') {
        res++;
    }
    return res + 1;
}

void createInvertedIndex(const char *in, const char *out) {
    std::wifstream input(in);

    int titleSymbols = 64 * 1024;
    int textSymbols = 32 * 1024 * 1024;
    int docId = 0;

    auto *notModifiedTitle = new wchar_t[titleSymbols];
    auto *title = new wchar_t[titleSymbols];
    auto *text = new wchar_t[textSymbols];

    auto *hashedIndex = new HashedInvertedIndex;
    hashedIndex->size = 25000;
    hashedIndex->indexes = new InvertedIndex[hashedIndex->size];

    while (
            input.getline(notModifiedTitle, titleSymbols) &&
            input.getline(title, titleSymbols) &&
            input.getline(text, textSymbols)
            ) {
        // parse title
        int pos = 0;
        int realStringEnd = -1;
        realStringEnd = getRealEnd(title);
        for (int i = 0; i < realStringEnd; i++) {
            bool isTokenEnd = i == realStringEnd - 1 || title[i] == L' ';
            if (!isTokenEnd) {
                continue;
            }
            int size = title[i] == L' ' ? i - pos : realStringEnd - pos;
            addToken(hashedIndex, title, pos, size, docId);
            pos = i + 1;
        }

        realStringEnd = getRealEnd(text);
        pos = 0;
        for (int i = 0; i < realStringEnd; i++) {
            bool isTokenEnd = i == realStringEnd - 1 || text[i] == L' ';
            if (!isTokenEnd) {
                continue;
            }
            int size = text[i] == L' ' ? i - pos : realStringEnd - pos;
            addToken(hashedIndex, text, pos, size, docId);
            pos = i + 1;
        }
        docId++;
        if (docId % 1000 == 0) {
            std::wcout << docId << L'\n';
            std::wcout.flush();
        }
    }

    std::ofstream output(out, std::ios::binary | std::ios::out);
    writeIndex(hashedIndex, output);

    delete[] notModifiedTitle;
    delete[] title;
    delete[] text;
    delete hashedIndex;
    input.close();
}

void createForwardIndex(const char *in, const char *out) {
    std::wifstream input(in);
    std::ofstream output(out, std::ios::binary | std::ios::out);

    int titleSymbols = 64 * 1024;
    int textSymbols = 32 * 1024 * 1024;
    int docId = 0;

    auto *notModifiedTitle = new wchar_t[titleSymbols];
    auto *title = new wchar_t[titleSymbols];
    auto *text = new wchar_t[textSymbols];

    while (
            input.getline(notModifiedTitle, titleSymbols) &&
            input.getline(title, titleSymbols) &&
            input.getline(text, textSymbols)
            ) {
        output.write((char*) &docId, sizeof(int));
        int size = wcslen(notModifiedTitle);
        output.write((char*) &size, sizeof(int) * 1);
        output.write((char*) notModifiedTitle, sizeof(wchar_t ) * size);
        docId++;
    }

    delete[] notModifiedTitle;
    delete[] title;
    delete[] text;
    input.close();
}
