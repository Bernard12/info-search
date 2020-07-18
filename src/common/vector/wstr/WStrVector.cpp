//
// Created by ivan on 18.07.2020.
//

#include "WStrVector.h"

WStrVector *createWStrVector(int size) {
    auto vec = new WStrVector;
    vec->items = new wchar_t *[size];
    vec->pos = 0;
    vec->size = size;
    return vec;
}

void pushWStr(WStrVector *vector, const wchar_t *value) {
    if (vector->pos == vector->size - 1) {
        int newSize = vector->size * 2;
        auto **vals = new wchar_t *[newSize];
        for (int i = 0; i < vector->pos; i++) {
            int s = wcslen(vector->items[i]);
            vals[i] = new wchar_t[s + 1];
            wcscpy(vals[i], vector->items[i]);
        }
        for (int i = 0; i < vector->pos; i++) {
            delete[] vector->items[i];
        }
        delete[] vector->items;
        vector->size = newSize;
        vector->items = vals;
    }
    int valueSize = wcslen(value);
    vector->items[vector->pos] = new wchar_t[valueSize + 1];
    wcscpy(vector->items[vector->pos++], value);
}

wchar_t* popWStr(WStrVector* vector) {
    if (vector->pos != 0) {
        return vector->items[--vector->pos];
    }
    return nullptr;
}