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
    #define SIZE 10
    const wchar_t* msg[SIZE] = {
            L"bla4",
            L"K && XX",
            L"(R) !((qr))    &&  (((x)) || g)",
            L"!((k) !iu)",
            L"((n)   || !qb)",
            L"!(   R    (vee))",
            L"(  a  b  )"
    };
    auto p = parseExpressionToPolish(L"!((k) !iu)");
    auto t = buildExpressionTree(p);
    // k iu ! && !
    delete p;
    delete t;
//    delete p;
//    delete t;
//    for (int i = 0; i < 7; i++) {
//        auto t = parseExpressionToPolish(msg[i]);
//        std::wcout << "\n------------" << '\n';
//        delete t;
//    }
//    auto w = createWStrVector(10);
//    delete w;
    return 0;
}
