//
// Created by ivan on 09.07.20.
//

#include "hash.h"

uint64_t hash(const wchar_t* str) {
    uint64_t res = 0;
    int size = wcslen(str);
    for (int i = 0; i < size; i++) {
        res = ((res << 5llu) + res) + str[i];
    }
    return res;
}