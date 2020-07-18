//
// Created by ivan on 18.07.2020.
//

#ifndef INFO_SEARCH_WSTRVECTOR_H
#define INFO_SEARCH_WSTRVECTOR_H

#include <cwchar>

struct WStrVector {
    wchar_t **items;
    int pos;
    int size;

    ~WStrVector() {
        for (int i = 0; i < pos; i++) {
            delete[] items[i];
        }
        delete[] items;
    }
};

WStrVector *createWStrVector(int size);

void pushWStr(WStrVector *vector, const wchar_t *value);

#endif //INFO_SEARCH_WSTRVECTOR_H
