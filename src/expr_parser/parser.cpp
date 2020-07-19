//
// Created by ivan on 18.07.2020.
//

#include "parser.h"

struct Scanner {
    wchar_t *str;
    int size;
    int cursor = 0;

    ~Scanner() {
        delete[] str;
    }
};

wchar_t peek(Scanner *sc) {
    if (sc->cursor == sc->size - 1) {
        return '\0';
    }
    int pos = sc->cursor + 1;
    return sc->str[pos];
}

wchar_t pop(Scanner *sc) {
    return sc->str[sc->cursor++];
}

Scanner *createScanner(const wchar_t *expr) {
    auto *scan = new Scanner;
    int size = wcslen(expr);
    scan->str = new wchar_t[size + 1];
    wcscpy(scan->str, expr);
    scan->size = size;
    return scan;
}

bool isOperator(const wchar_t c) {
    return c == L' ' || c == L'&' || c == L'|';
}

bool isTokenPart(const wchar_t c) {
    return iswalpha(c) || iswalnum(c);
}

bool isNextSameType(const wchar_t cur, const wchar_t next) {
    return (isOperator(cur) && isOperator(next)) || (isTokenPart(cur) && isTokenPart(next));
}

bool isEmptyString(const wchar_t *str) {
    bool res = true;
    int size = wcslen(str);
    for (int i = 0; i < size; i++) {
        res = res && str[i] == L' ';
    }
    return res;
}

wchar_t *trim(const wchar_t *str, wchar_t c) {
    int l = 0;
    int r = (int) wcslen(str) - 1;
    while (str[l] == c) {
        l++;
    }
    while (str[r] == c) {
        r--;
    }
    r++;
    int size = r - l;
    auto *res = new wchar_t[size + 1];
    for (int i = l, idx = 0; i < r; i++, idx++) {
        res[idx] = str[i];
    }
    res[size] = '\0';
    return res;
}

WStrVector *removeInvalidExpToken(WStrVector *vec) {
    auto res = createWStrVector(10);
    for (int i = 0; i < vec->pos; i++) {
        bool isOp = wcscmp(vec->items[i], L"&&") == 0 || wcscmp(vec->items[i], L"||") == 0;
        bool prevIsGood = i > 0 && (vec->items[i - 1][0] == L')' || iswalpha(vec->items[i - 1][0]));
        bool nextIsGood = i < vec->pos - 1 && (vec->items[i + 1][0] == L'(' || iswalpha(vec->items[i + 1][0]) ||
                                               vec->items[i + 1][0] == L'!');
        if (isOp && (!prevIsGood || !nextIsGood)) {
            continue;
        }
        int size = wcslen(vec->items[i]);
        auto tmp = new wchar_t[size + 1];
        wcscpy(tmp, vec->items[i]);
        pushWStr(res, tmp);
        delete[] tmp;
    }
    return res;
}

wchar_t *parseExpressionToken(const wchar_t *str) {
    if (isEmptyString(str)) {
        auto *t = new wchar_t[3];
        t[0] = '&';
        t[1] = '&';
        t[2] = '\0';
        return t;
    }
    return trim(str, L' ');
}

int getPriority(const wchar_t c) {
    if (c == L'!') {
        return 3;
    } else if (c == L'&') {
        return 2;
    } else if (c == L'|') {
        return 1;
    } else {
        return 0;
    }
}

WStrVector* parseExpressionToPolish(const wchar_t *expr) {
    auto vector = createWStrVector(1);
    auto sc = createScanner(expr);

    wchar_t temp[1024 * 1024];
    int pos = 0;


    wchar_t cur, next;
    while (true) {
        next = peek(sc);
        cur = pop(sc);
        temp[pos++] = cur;
        std::wcout << cur;
        if (next == L'\0') {
            // handle last symbol
            temp[pos] = '\0';
            pushWStr(vector, temp);
            pos = 0;
            break;
        }
        if (!isNextSameType(cur, next)) {
            temp[pos] = '\0';
            pushWStr(vector, temp);
            pos = 0;
        }
    }

    std::wcout << '\n';
//    std::wcout << L"Tokens: ";
    for (int i = 0; i < vector->pos; i++) {
        wchar_t *t = parseExpressionToken(vector->items[i]);
        delete[] vector->items[i];
        vector->items[i] = t;
    }
    auto validVec = removeInvalidExpToken(vector);

//    for (int i = 0; i < validVec->pos; i++) {
//        std::wcout << "\"" << validVec->items[i] << "\" ";
//    }

    WStrVector *operationStack = createWStrVector(10);
    WStrVector *polish = createWStrVector(10);

    for (int i = 0; i < validVec->pos; i++) {
        bool isOpenBracket = validVec->items[i][0] == L'(';
        if (isOpenBracket) {
            pushWStr(operationStack, validVec->items[i]);
            continue;
        }
        bool isCloseBracket = validVec->items[i][0] == L')';
        if (isCloseBracket) {
            wchar_t *top;
            while (true) {
                top = popWStr(operationStack);
                if (top[0] == '(') {
                    delete [] top;
                    break;
                }
                pushWStr(polish, top);
                delete[] top;
            }
            continue;
        }
        bool isOperator =
                validVec->items[i][0] == L'&' || validVec->items[i][0] == L'|' || validVec->items[i][0] == L'!';
        if (isOperator) {
            int priority = getPriority(validVec->items[i][0]);

            while (
                    operationStack->pos > 0 &&
                    getPriority(operationStack->items[operationStack->pos - 1][0]) >= priority
                    ) {
                wchar_t* top = popWStr(operationStack);
                pushWStr(polish, top);
                delete [] top;
            }
            pushWStr(operationStack, validVec->items[i]);
            continue;
        }
        pushWStr(polish, validVec->items[i]);
//        bool isOpenBracket = validVec->items[i][0] == '(';
    }

    while (operationStack->pos > 0) {
        wchar_t* top = popWStr(operationStack);
        pushWStr(polish, top);
        delete [] top;
    }

    for (int i = 0; i < polish->pos; i++) {
        std::wcout << polish->items[i] << L' ';
    }

    delete sc;
    delete validVec;
    delete vector;

    delete operationStack;
    return polish;
}