#include "./tokenize/Tokenize.h"
#include "./common/common.h"
#include "./boolean//index.h"

int main() {
    setupLocal();
    const char inPath[] = "/home/ivan/CLionProjects/info-search/parsed.txt";
    const char outPath[] = "/home/ivan/CLionProjects/info-search/parsed-tok.txt";
    const char binOut[] = "/home/ivan/CLionProjects/info-search/parsed-tokb.bin";
    createIndex(outPath, binOut);
//    std::ifstream in(binOut, std::ios::binary | std::ios::in);
////    int size = 0;
////    in.read((char *) &size, sizeof(int));
////    auto* s = new wchar_t[size];
////    in.read((char *) s, sizeof(wchar_t ) * size);
//    uint64_t t;
//    in.read((char*) &t, sizeof(uint64_t));
//
//    int docs = 0;
//    in.read((char*) &docs, sizeof(int));
//    int docid;
//    for (int i = 0; i < docs; i++) {
//        in.read((char*) &docid, sizeof(int));
//    }
    return 0;
}
