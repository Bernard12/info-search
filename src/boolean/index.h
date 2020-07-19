//
// Created by ivan on 10.07.2020.
//

#ifndef INFO_SEARCH_INDEX_H
#define INFO_SEARCH_INDEX_H

#include <iostream>
#include <string>
#include <fstream>
#include "../common/hash/hash.h"
#include "../common/vector/int/IntVector.h"
#include "../common/hash-index/hash-index.h"

void createInvertedIndex(const char* in, const char* out);
void createForwardIndex(const char* in, const char* out);

#endif //INFO_SEARCH_INDEX_H
