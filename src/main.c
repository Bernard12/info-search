#include <locale.h>
#include "./tokenize/Tokenize.h"

int main() {
    setlocale(LC_ALL, "");
    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed.txt";
    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
    tokenize(inPath, outPath);
    return 0;
}
