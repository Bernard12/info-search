#include "./tokenize/Tokenize.h"
#include "./common/common.h"
#include "./common/reverse-index/revert-index.h"
#include "./expr_parser/parser.h"
#include "./boolean/query.h"
#include "./common/forward-index/forward-index.h"


void test() {
    const wchar_t* t = L"1990";
}

int main() {
    setupLocal();
    const char inPath[] = "/home/ivan/CLionProjects/info-search/tparsed.txt";
    const char outPath[] = "/home/ivan/CLionProjects/info-search/tparsed-tok.txt";
    const char intest[] = "/home/ivan/CLionProjects/info-search/tparsed-tok.txt";
    const char invertedIndex[] = "/home/ivan/CLionProjects/info-search/tparsed-inv.bin";
    const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/tparsed-for.bin";
//    tokenize(inPath, outPath);
//    createInvertedIndex(intest, invertedIndex);
//    createForwardIndex(intest, forwardIndex);
//    createInvertedIndex(outPath, invertedIndex);
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
//    k iu ! && !
    auto p = parseExpressionToPolish(L"list && 1900");
    auto t = buildExpressionTree(p);

    std::ifstream in(invertedIndex, std::ios::binary | std::ios::in);
    auto index = loadIndex(in);
    in.close();

    std::wcout << '\n';
    queryClarification(index, t, 3);
    for (int i = 0; i < t->docs->pos; i++) {
        std::wcout << t->docs->items[i] << L' ';
    }
    delete p;
    delete t;
    delete index;
//    for (int i = 0; i < 7; i++) {
//        auto t = parseExpressionToPolish(msg[i]);
//        std::wcout << "\n------------" << '\n';
//        delete t;
//    }
//    auto w = createWStrVector(10);
//    delete w;
//    auto index = loadIndex(in);
//    in.close();
//    delete index;

//    auto v1 = createIntVector(5);
//    push(v1, 0);
//    push(v1, 1);

//    auto v2 = createIntVector(5);
//    push(v2, 0);
//    push(v2, 1);
//    push(v2, 5);
//    push(v2, 8);
//    push(v2, 12);

//    auto res = intersectVectors(v1, v2);
//    auto res = unionVectors(v1, v2);
//    auto res = notVector(v1, 3);

//    for (int i = 0; i < res->pos; i++) {
//        std::wcout << res->items[i] << ' ';
//    }

//    delete res;
//    delete v1;
//    delete v2;
    return 0;
}

