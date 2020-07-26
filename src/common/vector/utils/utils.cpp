//
// Created by ivan on 24.07.2020.
//

#include "utils.h"

IntVector *intersectVectors(IntVector *a, IntVector *b) {
    IntVector *res = createIntVector(10);
    for (int i = 0, j = 0; i < a->pos && j < b->pos;) {
        if (a->items[i] == b->items[j]) {
            push(res, a->items[i]);
            i++;
            j++;
        } else if (a->items[i] < b->items[j]) {
            i++;
        } else {
            j++;
        }
    }
    return res;
}

IntVector *unionVectors(IntVector *a, IntVector *b) {
    IntVector *res = createIntVector(10);

    if (a->pos == 0 || b->pos == 0) {
        for (int i = 0; i < a->pos; i++) {
            push(res, a->items[i]);
        }

        for (int i = 0; i < b->pos; i++) {
            push(res, b->items[i]);
        }

        return res;
    }

    for (int i = 0, j = 0; i < a->pos && j < b->pos;) {
        if (a->items[i] == b->items[j]) {
            push(res, a->items[i]);
            i++;
            j++;
        } else if (a->items[i] < b->items[j]) {
            push(res, a->items[i]);
            i++;
        } else {
            push(res, b->items[j]);
            j++;
        }
    }
    return res;
}

IntVector *notVector(IntVector *a, int maxIndex) {
    IntVector *res = createIntVector(10);

    for (int i = 0, j = 0; i < maxIndex; i++) {
        if (i == a->items[j]) {
            j = (j == a->pos) ? a->pos - 1 : j + 1;
        } else if ( i < a->items[j] ) {
            push(res, i);
        } else if ( i > a->items[j] ){
            j = (j == a->pos) ? a->pos - 1 : j + 1;
            push(res, i);
        }
    }
    return res;
}