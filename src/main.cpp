#include "./tokenize/Tokenize.h"
#include "./common/common.h"
#include "./boolean//index.h"

int main() {
    setupLocal();
    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed.txt";
    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
    const char binOut[] = "/home/ivan/CLionProjects/info-search/parsed-tok-bin.bin";
    createIndex(outPath, binOut);
    return 0;
}
