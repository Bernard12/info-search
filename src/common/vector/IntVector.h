//
// Created by ivan on 18.07.2020.
//

#ifndef INFO_SEARCH_INTVECTOR_H
#define INFO_SEARCH_INTVECTOR_H

struct IntVector {
    int *items;
    int pos;
    int size;

    ~IntVector() {
        delete[] items;
    }
};

IntVector *createVector(int size);
void push(IntVector *vector, int value);
bool has(IntVector *vector, int value);
#endif //INFO_SEARCH_INTVECTOR_H
