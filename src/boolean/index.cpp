//
// Created by ivan on 10.07.2020.
//

#include "index.h"

struct DocListNode {
    int docId;
    DocListNode *next;
};

struct TokenListNode {
    wchar_t *token;
    TokenListNode *next;
    DocListNode *docListRoot;
};

struct InvertedIndex {
    TokenListNode *tokenRoot;
};

int getRealEnd(const wchar_t *str) {
    int size = wcslen(str);
    int res = size - 1;
    while (str[res] == L' ') {
        res++;
    }
    return res + 1;
}

wchar_t *getSubstr(const wchar_t *str, int pos, int n) {
    auto *substr = new wchar_t[n + 1];
    wcsncpy(substr, str + pos, n);
    substr[n] = 0;
    return substr;
}

void addToken(InvertedIndex *index, const wchar_t *str, int pos, int n, int docId) {
    auto *token = getSubstr(str, pos, n);
    std::wcout << token << L' ';

    auto *docNode = new DocListNode;
    docNode->docId = docId;
    docNode->next = nullptr;

    if (index->tokenRoot == nullptr) {
        auto *root = new TokenListNode;
        root->token = token;
        root->docListRoot = docNode;
        root->next = nullptr;

        index->tokenRoot = root;
        return;
    }

    TokenListNode *root = index->tokenRoot;
    TokenListNode *prev = nullptr;
    while (root != nullptr) {
        if (wcscmp(root->token, token) == 0) {
            break;
        }
        prev = root;
        root = root->next;
    }
    // token not found
    if (root == nullptr) {
        auto *nextTokenNode = new TokenListNode;
        nextTokenNode->token = token;
        nextTokenNode->docListRoot = docNode;
        nextTokenNode->next = nullptr;

        prev->next = nextTokenNode;
    } else {
        DocListNode* docRoot = root->docListRoot;
        bool isDocPresent = docRoot->docId == docId;
        while (docRoot->next) {
            isDocPresent = isDocPresent || docRoot->docId == docId;
            docRoot = docRoot->next;
            isDocPresent = isDocPresent || docRoot->docId == docId;
        }

        if (!isDocPresent) {
            docRoot->next = docNode;
        } else {
            delete docNode;
        }
        delete[] token;
    }
}

void freeIndex(InvertedIndex* index) {
    TokenListNode* tmp;
    TokenListNode* cur = index->tokenRoot;

    DocListNode* docTemp;
    DocListNode* docCur;
    while (cur) {
        tmp = cur;
        cur = cur->next;

        docCur = tmp->docListRoot;
        while (docCur) {
            docTemp = docCur;
            docCur = docCur->next;
            delete docTemp;
        }

        delete[] tmp->token;
        delete tmp;
    }
    delete index;
}

void createIndex(const char *in, const char *out) {
    std::wifstream input(in);

    int titleSymbols = 64 * 1024;
    int textSymbols = 32 * 1024 * 1024;
    int docId = 0;

    auto *title = new wchar_t[titleSymbols];
    auto *text = new wchar_t[textSymbols];

    auto *index = new InvertedIndex;

    while (input.getline(title, titleSymbols) && input.getline(text, textSymbols)) {
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
            addToken(index, title, pos, size, docId);
            pos = i + 1;
        }
        std::wcout << '\n';

        realStringEnd = getRealEnd(text);
        pos = 0;
        for (int i = 0; i < realStringEnd; i++) {
            bool isTokenEnd = i == realStringEnd - 1 || text[i] == L' ';
            if (!isTokenEnd) {
                continue;
            }
            int size = text[i] == L' ' ? i - pos : realStringEnd - pos;
            addToken(index, text, pos, size, docId);
            pos = i + 1;
        }
        std::wcout << L'\n';
        docId++;
    }

    delete[] title;
    delete[] text;
    freeIndex(index);
    input.close();
}
