//
// Created by ivan on 24.07.2020.
//

#ifndef INFO_SEARCH_UTILS_H
#define INFO_SEARCH_UTILS_H

#include "../int/IntVector.h"

IntVector* intersectVectors(IntVector* a, IntVector* b);
IntVector* unionVectors(IntVector* a, IntVector* b);
IntVector* notVector(IntVector* a, int maxIndex);

#endif //INFO_SEARCH_UTILS_H
