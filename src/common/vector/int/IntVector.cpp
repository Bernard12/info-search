//
// Created by ivan on 18.07.2020.
//

#include "IntVector.h"

IntVector *createIntVector(int size) {
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