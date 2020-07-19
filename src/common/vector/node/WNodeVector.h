//
// Created by ivan on 19.07.2020.
//

#ifndef INFO_SEARCH_WNODEVECTOR_H
#define INFO_SEARCH_WNODEVECTOR_H

struct Node {
    wchar_t *value;

    Node *left;
    Node *right;

    ~Node() {
        delete left;
        delete right;
        delete[] value;
    }
};

struct WNodeVector {
    Node* items;
    int pos;
    int size;

    ~WNodeVector() {
        delete[] items;
    }
};

WNodeVector *createWNodeVector(int size);

void pushWNode(WNodeVector *vector, Node* node);
Node* popWNode(WNodeVector* vector);

#endif //INFO_SEARCH_WNODEVECTOR_H
