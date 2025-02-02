//
// Created by ivan on 19.07.2020.
//

#include "hash-index.h"
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
        root->docArray = createIntVector(5);
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
        nextTokenNode->docArray = createIntVector(5);
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
void addHash(HashedInvertedIndex *hashedIndex, uint64_t hash, int docId) {
//    std::wcout << token << L' ';
    uint64_t h = hash % hashedIndex->size;
    InvertedIndex *index = &(hashedIndex->indexes[h]);

    if (index->tokenRoot == nullptr) {
        auto *root = new TokenListNode;
        root->token = nullptr;
        root->hash = hash;
        root->docArray = createIntVector(5);
        push(root->docArray, docId);
        root->next = nullptr;

        index->tokenRoot = root;
        return;
    }

    TokenListNode *root = index->tokenRoot;
    TokenListNode *prev = nullptr;
    // need faster algo to search token
    while (root != nullptr) {
        uint64_t rootTokenHash = root->hash;
        if (hash == rootTokenHash) {
            break;
        }
        prev = root;
        root = root->next;
    }
    // token not found
    if (root == nullptr) {
        auto *nextTokenNode = new TokenListNode;
        nextTokenNode->token = nullptr;
        nextTokenNode->hash = hash;
        nextTokenNode->docArray = createIntVector(5);
        push(nextTokenNode->docArray, docId);
        nextTokenNode->next = nullptr;

        prev->next = nextTokenNode;
    } else {
        IntVector *docIds = root->docArray;
        bool isDocPresent = has(docIds, docId);

        if (!isDocPresent) {
            push(docIds, docId);
        }
    }
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
            out.write((char *) &docs->pos, sizeof(int));
            for (int j = 0; j < docs->pos; j++) {
                out.write((char *) &docs->items[j], sizeof(int));
            }

            tokenHead = tokenHead->next;
        }
    }
}

HashedInvertedIndex* loadIndex(std::istream& in) {
    uint64_t hash;
    int maxId = -10;

    auto *result = new HashedInvertedIndex;
    result->size = 25000;
    result->indexes = new InvertedIndex[result->size];

    while ( in.read((char *) &hash, sizeof(uint64_t)) ) {
        int docCount = 0;
        in.read((char*) &docCount, sizeof(int));
//        std::wcout << "Hash: " << hash << "; doc count: " << docCount << '\n';
        for (int i = 0; i < docCount; i++) {
            int docId;
            in.read((char*) &docId, sizeof(int));
//            std::wcout << docId << ' ';
            maxId = std::max(maxId, docId);
            addHash(result, hash, docId);
        }
//        std::wcout << '\n';
    }
//    std::wcout << "Max id is: " << maxId << '\n';
    return result;
}

int findMaxDocId(HashedInvertedIndex* index) {
    int res = 0;
    for (int i = 0; i < index->size; i++) {
        if (index->indexes[i].tokenRoot == nullptr) {
            continue;
        }
        TokenListNode* root = index->indexes[i].tokenRoot;
        while (root != nullptr) {
            auto docs = root->docArray;
            for (int j = 0; j < docs->pos; j++) {
                res = docs->items[j] > res ? docs->items[j] : res;
            }
            root = root->next;
        }
    }
    return res;
}