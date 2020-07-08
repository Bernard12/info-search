//
// Created by ivan on 08.07.2020.
//

#ifndef INFO_SEARCH_TOKENIZE_H
#define INFO_SEARCH_TOKENIZE_H

#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define KB 1024
#define MB 1024 * 1024

#define READ_TITLE 0
#define READ_TEXT 1
#define WRITE_OUTPUT 2


void tokenize(const char* inPath, const char* outPath);


#endif //INFO_SEARCH_TOKENIZE_H
