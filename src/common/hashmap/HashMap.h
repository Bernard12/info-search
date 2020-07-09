//
// Created by ivan on 09.07.2020.
//

#ifndef INFO_SEARCH_HASHMAP_H
#define INFO_SEARCH_HASHMAP_H


struct ListNode {
    void* value;
    ListNode* next;
};

struct Bucket {
    ListNode* itemsList;
};

/*
 * Current usage: wchar_t* <-> int
 */
struct HashMap {
    Bucket* buckets;
    int bucketsCount;
};

HashMap* createHashMap(int);
void freeHashMap(HashMap*);

#endif //INFO_SEARCH_HASHMAP_H
