//
// Created by ivan on 09.07.20.
//

#include "hash.h"

uint64_t hash(const wchar_t* str) {
    uint64_t res = 0;
    for (int i = 0; i < wcslen(str); i++) {
        res = res * 31 + str[i];
    }
    return res;
}