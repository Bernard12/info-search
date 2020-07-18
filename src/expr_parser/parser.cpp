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

void parseExpression(const wchar_t *expr) {
    auto vector = createWStrVector(1);
    auto sc = createScanner(expr);

    wchar_t temp[1024 * 1024];
    int pos = 0;


    wchar_t cur, next;
    while (true) {
        next = peek(sc);
        cur = pop(sc);
        temp[pos++]=cur;
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
    std::wcout << L"Tokens: ";
    for (int i = 0; i < vector->pos; i++) {
        std::wcout << L"\"" << vector->items[i] << L"\", ";
    }
    delete sc;
    delete vector;
}