//
// Created by ivan on 25.07.2020.
//

#ifndef INFO_SEARCH_FORWARD_INDEX_H
#define INFO_SEARCH_FORWARD_INDEX_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "../vector/wstr/WStrVector.h"

void createForwardIndex(const char* in, const char* out);
WStrVector* readForwardIndex(const char* in);

#endif //INFO_SEARCH_FORWARD_INDEX_H
