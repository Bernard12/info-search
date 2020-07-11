#include "./tokenize/Tokenize.h"
#include "./common/common.h"
#include "./boolean//index.h"

int main() {
    setupLocal();
    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed.txt";
    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
    const char inversedIndex[] = "/home/ivan/CLionProjects/info-search/parsed-inv.bin";
    const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/parsed-for.bin";
//    tokenize(inPath, outPath);
    createInvertedIndex(outPath, inversedIndex);
    createForwardIndex(outPath, forwardIndex);
    return 0;
}
