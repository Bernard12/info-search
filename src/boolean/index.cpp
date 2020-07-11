//
// Created by ivan on 10.07.2020.
//

#include "index.h"

// for doc list
struct IntVector {
    int *items;
    int pos;
    int size;

    ~IntVector() {
        delete[] items;
    }
};

struct TokenListNode {
    wchar_t *token;
    uint64_t hash;
    TokenListNode *next;
    IntVector *docArray;

    ~TokenListNode() {
        delete[] token;
        delete docArray;
        delete next;
    }
};

struct InvertedIndex {
    TokenListNode *tokenRoot;

    ~InvertedIndex() {
        delete tokenRoot;
    }
};

struct HashedInvertedIndex {
    InvertedIndex *indexes;
    int size;

    ~HashedInvertedIndex() {
        delete[] indexes;
    }
};

IntVector *createVector(int size) {
    auto *vec = new IntVector;
    vec->items = new int[size];
    vec->pos = 0;
    vec->size = size;
    return vec;
}

void push(IntVector *vector, int value) {
    if (vector->pos == vector->size - 1) {
        int newSize = vector->size * 2;
        int *vals = new int[newSize];
        for (int i = 0; i < vector->size; i++) {
            vals[i] = vector->items[i];
        }
        delete[] vector->items;
        vector->size = newSize;
        vector->items = vals;
    }
    vector->items[vector->pos++] = value;
}

bool has(IntVector *vector, int value) {
    int l = 0;
    int r = vector->pos - 1;
    while (l <= r) {
        int mid = (r + l) / 2;
        if (vector->items[mid] == value) {
            return true;
        } else if (vector->items[mid] > value) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return false;
}

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
    for (int i = 0; i < n; i++) {
        substr[i] = towlower(substr[i]);
    }
    return substr;
}

void addToken(HashedInvertedIndex *hashedIndex, const wchar_t *str, int pos, int n, int docId) {
    auto *token = getSubstr(str, pos, n);
//    std::wcout << token << L' ';
    uint64_t th = hash(token) % hashedIndex->size;
    InvertedIndex *index = &(hashedIndex->indexes[th]);

    if (index->tokenRoot == nullptr) {
        auto *root = new TokenListNode;
        root->token = token;
        root->hash = hash(token);
        root->docArray = createVector(5);
        push(root->docArray, docId);
        root->next = nullptr;

        index->tokenRoot = root;
        return;
    }

    TokenListNode *root = index->tokenRoot;
    TokenListNode *prev = nullptr;
    uint64_t tokenHash = hash(token);
    // need faster algo to search token
    while (root != nullptr) {
        uint64_t rootTokenHash = root->hash;
        if (tokenHash == rootTokenHash && wcscmp(root->token, token) == 0) {
            break;
        }
        prev = root;
        root = root->next;
    }
    // token not found
    if (root == nullptr) {
        auto *nextTokenNode = new TokenListNode;
        nextTokenNode->token = token;
        nextTokenNode->hash = hash(token);
        nextTokenNode->docArray = createVector(5);
        push(nextTokenNode->docArray, docId);
        nextTokenNode->next = nullptr;

        prev->next = nextTokenNode;
    } else {
        IntVector *docIds = root->docArray;
        bool isDocPresent = has(docIds, docId);

        if (!isDocPresent) {
            push(docIds, docId);
        }

        delete[] token;
    }
}

void freeHashedIndex(HashedInvertedIndex *index) {
    delete index;
}

void writeIndex(HashedInvertedIndex *index, std::ofstream &out) {
    int size = index->size;
    for (int i = 0; i < size; i++) {
        InvertedIndex *cur = index->indexes + i;
        if (cur->tokenRoot == nullptr) {
            continue;
        }
        TokenListNode *tokenHead = cur->tokenRoot;
        while (tokenHead != nullptr) {
            out.write((char *) &tokenHead->hash, sizeof(uint64_t));

            IntVector *docs = tokenHead->docArray;
            out.write((char *) &docs->size, sizeof(int));
            for (int j = 0; j < docs->size; j++) {
                out.write((char *) &docs->items[j], sizeof(int));
            }

            tokenHead = tokenHead->next;
        }
    }
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
        output.write((char*) notModifiedTitle, sizeof(wchar_t ) * wcslen(notModifiedTitle));
        docId++;
    }

    delete[] notModifiedTitle;
    delete[] title;
    delete[] text;
    input.close();
}
