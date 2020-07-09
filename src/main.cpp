#include "./tokenize/Tokenize.h"
#include "./common/common.h"

int main() {
    setupLocal();
    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed1.txt";
    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
    tokenize(inPath, outPath);
    return 0;
}
