//
// Created by ivan on 25.07.2020.
//

#ifndef INFO_SEARCH_QUERY_H
#define INFO_SEARCH_QUERY_H

#include "../common/vector/node/WNodeVector.h"
#include "../common/vector/utils/utils.h"
#include "../common/hash-index/hash-index.h"
#include "../common/hash/hash.h"

void queryClarification(HashedInvertedIndex* index, Node* root, int docCount);

#endif //INFO_SEARCH_QUERY_H
