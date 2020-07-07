#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "./string/String.h"

int main() {
    const wchar_t st[25] = L"Привет мир";
    String* s = createString(st, 9);
    wchar_t t = getChar(s, 0);
//    wprintf(&t);
    wprintf(L"%ls!", st);
//    deleteString(&s);
    return 0;
}
