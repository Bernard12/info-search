//
// Created by ivan on 19.07.2020.
//

#include "WNodeVector.h"

WNodeVector *createWNodeVector(int size) {
    auto vec = new WNodeVector;
    vec->items = new Node*[size];
    vec->pos = 0;
    vec->size = size;
    return vec;
}

void pushWNode(WNodeVector *vector, Node *node) {
    if (vector->pos == vector->size - 1) {
        int newSize = vector->size * 2;
        Node** vals = new Node*[newSize];
        for (int i = 0; i < vector->size; i++) {
            vals[i] = vector->items[i];
        }
        delete[] vector->items;
        vector->size = newSize;
        vector->items = vals;
    }
    vector->items[vector->pos++] = node;
}

Node *popWNode(WNodeVector *vector) {
    if (vector->pos != 0) {
        return vector->items[--vector->pos];
    }
    return nullptr;
}