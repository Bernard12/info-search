//
// Created by ivan on 19.07.2020.
//

#ifndef INFO_SEARCH_WNODEVECTOR_H
#define INFO_SEARCH_WNODEVECTOR_H

#include "../int/IntVector.h"

struct Node {
    wchar_t *value;
    IntVector* docs = nullptr;

    Node *left = nullptr;
    Node *right = nullptr;

    ~Node() {
        delete left;
        delete right;
        delete docs;
        delete[] value;
    }
};

struct WNodeVector {
    Node** items;
    int pos;
    int size;

    ~WNodeVector() {
        for (int i = 0; i < pos; i++) {
            delete items[i];
        }
        delete[] items;
    }
};

WNodeVector *createWNodeVector(int size);

void pushWNode(WNodeVector *vector, Node* node);
Node* popWNode(WNodeVector* vector);

#endif //INFO_SEARCH_WNODEVECTOR_H
