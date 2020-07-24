#include "./tokenize/Tokenize.h"
#include "./common/common.h"
#include "./boolean/index.h"
#include "./expr_parser/parser.h"
#include "./common/hash-index/hash-index.h"
#include "./common/vector/utils/utils.h"


int main() {
    setupLocal();
//    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed.txt";
//    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
//    const char intest[] = "/home/ivan/CLionProjects/info-search/test-tok.txt";
//    const char inversedIndex[] = "/home/ivan/CLionProjects/info-search/test-inv.bin";
//    const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/test-for.bin";
//    tokenize(inPath, outPath);
//    createInvertedIndex(intest, inversedIndex);
//    createForwardIndex(intest, forwardIndex);
//    createInvertedIndex(outPath, inversedIndex);
//    createForwardIndex(outPath, forwardIndex);
//    const wchar_t* msg = L"!((N))";
//    #define SIZE 10
//    const wchar_t* msg[SIZE] = {
//            L"bla4",
//            L"K && XX",
//            L"(R) !((qr))    &&  (((x)) || g)",
//            L"!((k) !iu)",
//            L"((n)   || !qb)",
//            L"!(   R    (vee))",
//            L"(  a  b  )"
//    };
//    auto p = parseExpressionToPolish(L"!((k) !iu)");
//    auto t = buildExpressionTree(p);
    // k iu ! && !
//    delete p;
//    delete t;
//    delete p;
//    delete t;
//    for (int i = 0; i < 7; i++) {
//        auto t = parseExpressionToPolish(msg[i]);
//        std::wcout << "\n------------" << '\n';
//        delete t;
//    }
//    auto w = createWStrVector(10);
//    delete w;
//    std::ifstream in(inversedIndex, std::ios::binary | std::ios::in);
//    auto index = loadIndex(in);
//    in.close();
//    delete index;

    auto v1 = createIntVector(5);
    push(v1, 0);
    push(v1, 5);
    push(v1, 12);

//    auto v2 = createIntVector(5);
//    push(v2, 0);
//    push(v2, 1);
//    push(v2, 5);
//    push(v2, 8);
//    push(v2, 12);

//    auto res = intersectVectors(v1, v2);
//    auto res = unionVectors(v1, v2);
    auto res = notVector(v1, 15);

    for (int i = 0; i < res->pos; i++) {
        std::wcout << res->items[i] << ' ';
    }

    delete res;
    delete v1;
//    delete v2;
    return 0;
}
