//
// Created by ivan on 18.07.2020.
//

#include "WcharVector.h"

WcharStrVector *createStrVector(int size) {
    auto *vec = new WcharStrVector;
    vec->items = new wchar_t*[size];
    vec->pos = 0;
    vec->size = size;
    return vec;
}

void push(WcharStrVector *vector, const wchar_t* value) {
    if (vector->pos == vector->size - 1) {
        int newSize = vector->size * 2;
        auto **vals = new wchar_t*[newSize];
        for (int i = 0; i < vector->size; i++) {
            vals[i] = vector->items[i];
        }
        for (int i = 0; i < vector->size; i++ ){
            delete[] vector->items[i];
        }
        vector->size = newSize;
        vector->items = vals;
    }
    int valueSize = wcslen(value);
    vector->items[vector->pos] = new wchar_t[valueSize];
    wcscpy(vector->items[vector->pos++], value);
}