//
// Created by ivan on 07.07.2020.
//

#include "String.h"

String* createString(const wchar_t* chars, int sz) {
    String* str = (String*) malloc(sizeof(String));
    str->symbols = malloc(sizeof(const wchar_t) * sz + 1);
    memset(str->symbols, 0, sizeof(wchar_t) * sz + 1);
    memcpy(str->symbols, chars, sizeof(wchar_t) * sz);
    str->size = sz;
    return str;
}

void deleteString(String** string) {
    free(&string);
}

wchar_t getChar(String* string, int idx) {
    if (idx < 0 || idx > string->size) {
        return 0;
    }
    return string->symbols[idx];
}

