//
// Created by ivan on 18.07.2020.
//

#ifndef INFO_SEARCH_INTVECTOR_H
#define INFO_SEARCH_INTVECTOR_H

#include <cwchar>

struct WcharStrVector {
    wchar_t** items;
    int pos;
    int size;

    ~WcharStrVector() {
        for (int i = 0; i < size; i++) {
            delete[] items[i];
        }
    }
};

WcharStrVector *createStrVector(int size);
void push(WcharStrVector *vector, const wchar_t* value);
#endif //INFO_SEARCH_INTVECTOR_H
