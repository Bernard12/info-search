//
// Created by ivan on 18.07.2020.
//

#ifndef INFO_SEARCH_PARSER_H
#define INFO_SEARCH_PARSER_H

#include <cstring>
#include <cwchar>
#include <cstdio>
#include <iostream>
#include "../common/vector/wstr/WStrVector.h"
#include "../common/vector/node/WNodeVector.h"

WStrVector *parseExpressionToPolish(const wchar_t *expr);
Node* buildExpressionTree(WStrVector* polish);

#endif //INFO_SEARCH_PARSER_H
