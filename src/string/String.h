//
// Created by ivan on 07.07.2020.
//

#ifndef INFO_SEARCH_STRING_H
#define INFO_SEARCH_STRING_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    wchar_t *symbols;
    int size;
} String;

String *createString(const wchar_t *, int);

void deleteString(String *);

wchar_t getChar(String *, int);

#endif //INFO_SEARCH_STRING_H
