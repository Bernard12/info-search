//
// Created by ivan on 25.07.2020.
//

#ifndef INFO_SEARCH_REVERT_INDEX_H
#define INFO_SEARCH_REVERT_INDEX_H

#include <iostream>
#include <string>
#include <fstream>
#include "../hash/hash.h"
#include "../vector/int/IntVector.h"
#include "../hash-index/hash-index.h"

void createInvertedIndex(const char* in, const char* out);

#endif //INFO_SEARCH_REVERT_INDEX_H
