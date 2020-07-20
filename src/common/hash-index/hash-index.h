//
// Created by ivan on 19.07.2020.
//

#ifndef INFO_SEARCH_HASH_INDEX_H
#define INFO_SEARCH_HASH_INDEX_H

#include <iostream>
#include <string>
#include <fstream>
#include "../hash/hash.h"
#include "../vector/int/IntVector.h"


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
    TokenListNode *tokenRoot = nullptr;

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

void addToken(HashedInvertedIndex *hashedIndex, const wchar_t *str, int pos, int n, int docId);
void addHash(HashedInvertedIndex *hashedIndex, uint64_t hash, int docId);
void writeIndex(HashedInvertedIndex *index, std::ofstream &out);
HashedInvertedIndex* loadIndex(std::istream& in);
#endif //INFO_SEARCH_HASH_INDEX_H
