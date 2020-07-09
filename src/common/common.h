//
// Created by ivan on 09.07.20.
//

#ifndef INFO_SEARCH_COMMON_H
#define INFO_SEARCH_COMMON_H

#include <iostream>

void setupLocal() {
    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale("en_US.UTF-8"));
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));
}

#endif //INFO_SEARCH_COMMON_H
