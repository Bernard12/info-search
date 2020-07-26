//
// Created by ivan on 25.07.2020.
//

#include "query.h"

IntVector *findDocs(HashedInvertedIndex *index, uint64_t hash) {
    IntVector *res = createIntVector(10);
    auto bucket = index->indexes + hash % index->size;

    if (bucket->tokenRoot == nullptr) {
        return res;
    }

    TokenListNode *node = bucket->tokenRoot;
    while (node != nullptr && node->hash != hash) {
        node = node->next;
    }

    if (node != nullptr) {
        for(int i = 0; i < node->docArray->pos; i++) {
            push(res, node->docArray->items[i]);
        }
    }
    return res;
}

void queryClarification(HashedInvertedIndex *index, Node *root, int documentCount) {
    bool isNotOperation = root->value[0] != '&' && root->value[0] != '|' && root->value[0] != '!';
    if (isNotOperation) {
        root->docs = findDocs(index, hash(root->value));
        return;
    }

    if (root->left != nullptr) {
        queryClarification(index, root->left, documentCount);
    }

    if (root->right != nullptr) {
        queryClarification(index, root->right, documentCount);
    }

    bool isNot = root->value[0] == '!';
    if (isNot) {
        root->docs = notVector(root->left->docs, documentCount);
        return;
    }
    bool isAnd = root->value[0] == '&';
    if (isAnd) {
        root->docs = intersectVectors(root->left->docs, root->right->docs);
        return;
    }
    bool isOr = root->value[0] == '|';
    if (isOr) {
        root->docs = unionVectors(root->left->docs, root->right->docs);
        return;
    }
}