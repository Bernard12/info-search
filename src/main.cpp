#include "./tokenize/Tokenize.h"
#include "./common/common.h"
#include "./common/reverse-index/revert-index.h"
#include "./expr_parser/parser.h"
#include "./boolean/query.h"
#include "./common/forward-index/forward-index.h"

#include <getopt.h>
#include <clocale>

#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
    setupLocal();
    int optIndex = 0;

    bool isFile = false;
    const char *queryFilePath = nullptr;
    const char *query = nullptr;

    while ((optIndex = getopt(argc, argv, "f:q:")) != -1) {
        switch (optIndex) {
            case 'f':
                isFile = true;
                queryFilePath = optarg;
                break;
            case 'q':
                query = optarg;
        }
    }

    if (isFile) {
        std::wcout << "Current mode is File" << '\n';
        std::wcout << "Path: " << queryFilePath << '\n';
    } else {
        // Mode for nodejs backend
//        const char invertedIndex[] = "/home/ivan/CLionProjects/info-search/tparsed-inv.bin";
//        const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/tparsed-for.bin";
        const char invertedIndex[] = "/home/ivan/CLionProjects/info-search/parsed-inv.bin";
        const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/parsed-for.bin";
        std::ifstream in(invertedIndex, std::ios::binary | std::ios::in);
        auto rIndex = loadIndex(in);
        auto fIndex = readForwardIndex(forwardIndex);
        int maxDocId = findMaxDocId(rIndex);

        std::wstring str;

        while (1) {
            std::getline(std::wcin, str);
            std::wcerr << "[DEBUG]" << " Received query: " << str << '\n';
            std::wcerr << "[DEBUG]" << " Parsing query" << '\n';
            auto polish = parseExpressionToPolish(str.data());
            std::wcerr << "[DEBUG]" << " Building expression tree" << '\n';
            auto tree = buildExpressionTree(polish);
            std::wcerr << "[DEBUG]" << " Perform search in index " << '\n';
            // TODO: write function to find max docId!
            queryClarification(rIndex, tree, maxDocId + 1);
            std::cout << tree->docs->pos << '\n';
            std::cout.flush();
            for (int i = 0; i < tree->docs->pos; i++) {
                std::wcout << fIndex->items[tree->docs->items[i]] << std::endl;
            }
            break;
        }

        delete rIndex;
        delete fIndex;
    }

//    const char inPath[] = "/home/ivan/CLionProjects/info-search/tparsed.txt";
//    const char outPath[] = "/home/ivan/CLionProjects/info-search/tparsed-tok.txt";
//    const char intest[] = "/home/ivan/CLionProjects/info-search/tparsed-tok.txt";
//    const char invertedIndex[] = "/home/ivan/CLionProjects/info-search/tparsed-inv.bin";
//    const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/tparsed-for.bin";
//    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed.txt";
//    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
//    const char invertedIndex[] = "/home/ivan/CLionProjects/info-search/parsed-inv.bin";
//    const char forwardIndex[] = "/home/ivan/CLionProjects/info-search/parsed-for.bin";
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
//    auto p = parseExpressionToPolish(L"list && 1900");
//    auto t = buildExpressionTree(p);
////
//    std::ifstream in(invertedIndex, std::ios::binary | std::ios::in);
//    auto index = loadIndex(in);
//    in.close();
////
//    std::wcout << '\n';
//    queryClarification(index, t, 3);
////
//    auto res = readForwardIndex(forwardIndex);
////
//    for (int i = 0; i < t->docs->pos; i++) {
//        std::wcout << res->items[t->docs->items[i]] << L'\n';
//    }
//    delete p;
//    delete t;
//    delete res;
//    delete index;
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
//
//    auto v2 = createIntVector(5);
//
////    auto res = intersectVectors(v1, v2);
////    auto res = unionVectors(v1, v2);
//    auto res = notVector(v2, 3);
//
//    for (int i = 0; i < res->pos; i++) {
//        std::wcout << res->items[i] << ' ';
//    }

//    delete res;
//    delete v1;
//    delete v2;
    return 0;
}

