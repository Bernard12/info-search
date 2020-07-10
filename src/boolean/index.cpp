//
// Created by ivan on 10.07.2020.
//

#include "index.h"

struct ListNode {
    int docId;
    ListNode * next;
};

struct InvertedIndex {
    int tokenHash;
    ListNode* docIdsList;
};

int getRealEnd(const wchar_t * str) {
    int size = wcslen(str);
    int res = size - 1;
    while (str[res] == L' ') {
        res++;
    }
    return res + 1;
}

void getSubstr(const wchar_t* str, int pos, int n) {
    auto* substr = (wchar_t *) malloc(sizeof(wchar_t) * n + 1);
    wcsncpy(substr, str + pos, n);
    substr[n] = 0;
    std::wcout << substr << ' ';
    free(substr);
}

void createIndex(const char* in, const char* out) {
    std::wifstream input(in);

    int titleSymbols = 64 * 1024;
    int textSymbols = 32 * 1024 * 1024;

    auto* title = (wchar_t *) malloc(sizeof(wchar_t) *titleSymbols);
    auto* text = (wchar_t *) malloc(sizeof(wchar_t ) * textSymbols);

//    auto* index = (InvertedIndex*) malloc(sizeof(InvertedIndex) * 1);

    while (input.getline(title, titleSymbols) && input.getline(text, textSymbols)) {
        // parse title
        int pos = 0;
        int realStringEnd = -1;
        realStringEnd = getRealEnd(title);
        for (int i = 0; i < realStringEnd; i++) {
            if (i == realStringEnd - 1) {
                int size = realStringEnd - pos;
                getSubstr(title, pos, size);
            } else if (title[i] == L' ') {
                int size = i - pos;
                getSubstr(title, pos, size);
                pos = i + 1;
                continue;
            }
        }
        std::wcout << '\n';

        realStringEnd = getRealEnd(text);
        pos = 0;
        for (int i = 0; i < realStringEnd; i++) {
            if (i == realStringEnd - 1) {
                int size = realStringEnd - pos;
                getSubstr(text, pos, size);
            } else if (text[i] == L' ') {
                int size = i - pos;
                getSubstr(text, pos, size);
                pos = i + 1;
                continue;
            }
        }
        std::wcout << L'\n';
    }

    free(title);
    free(text);
    input.close();
}
