//
// Created by ivan on 25.07.2020.
//

#include "forward-index.h"

void createForwardIndex(const char *in, const char *out) {
    std::wifstream input(in);
    std::ofstream output(out, std::ios::binary | std::ios::out);

    int titleSymbols = 64 * 1024;
    int textSymbols = 32 * 1024 * 1024;
    int docId = 0;

    auto *notModifiedTitle = new wchar_t[titleSymbols];
    auto *title = new wchar_t[titleSymbols];
    auto *text = new wchar_t[textSymbols];

    while (
            input.getline(notModifiedTitle, titleSymbols) &&
            input.getline(title, titleSymbols) &&
            input.getline(text, textSymbols)
            ) {
        output.write((char*) &docId, sizeof(int));
        int size = wcslen(notModifiedTitle);
        output.write((char*) &size, sizeof(int) * 1);
        output.write((char*) notModifiedTitle, sizeof(wchar_t ) * size);
        docId++;
    }

    delete[] notModifiedTitle;
    delete[] title;
    delete[] text;
    input.close();
}

WStrVector* readForwardIndex(const char* inPath) {
    std::ifstream in(inPath);
    WStrVector* res = createWStrVector(10);
    int id, size;
    wchar_t temp[1024 * 16] = {0};
    while (
            in.read((char*) &id, sizeof(int)) &&
            in.read((char*) &size, sizeof(int)) &&
            in.read((char*) &temp, sizeof(wchar_t ) * size)
            ) {
        pushWStr(res, temp);
        std::memset(temp, 0, 1024 * 16);
    }
    return res;
}