//
// Created by ivan on 09.07.2020.
//

#include "HashMap.h"


HashMap* createHashMap(int buckets) {
    auto* res = new HashMap();
    res->bucketsCount = buckets;
    res->buckets = new Bucket[buckets];
    for (int i = 0; i < buckets; i++) {
        res->buckets[i].itemsList = nullptr;
    }
    return res;
}

void freeHashMap(HashMap* hashMap) {
    delete[] hashMap->buckets;
    delete hashMap;
}
