#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "./string/String.h"

int main() {
    setlocale(LC_ALL, "");
    const wchar_t st[25] = L"Привет мир";
    String* s = createString(st, 9);
    wchar_t t = getChar(s, 0);
    wprintf(L"%lc", t);
    deleteString(s);
    return 0;
}
