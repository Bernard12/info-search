#include "./tokenize/Tokenize.h"
#include "./common/common.h"
#include "./boolean/index.h"
#include "./expr_parser/parser.h"



int main() {
    setupLocal();
//    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed.txt";
//    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
//    const char inversedIndex[] = "/home/ivan/CLionProjects/info-search/parsed-inv.bin";
//    const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/parsed-for.bin";
//    tokenize(inPath, outPath);
//    createInvertedIndex(outPath, inversedIndex);
//    createForwardIndex(outPath, forwardIndex);
//    const wchar_t* msg = L"!((N))";
    int size = 10;
    #define SIZE 10
    const wchar_t* msg[SIZE] = {
            L"bla4",
            L"K && XX",
            L"(R) !((qr))    &&  (((x)) || g)",
            L"!((k) !iu)"
    };

    for (int i = 0; i < 4; i++) {
        parseExpression(msg[i]);
        std::wcout << "\n------------" << '\n';
    }
//    auto w = createWStrVector(10);
//    delete w;
    return 0;
}
