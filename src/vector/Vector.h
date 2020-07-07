//
// Created by ivan on 07.07.2020.
//

#ifndef INFO_SEARCH_VECTOR_H
#define INFO_SEARCH_VECTOR_H

template<typename T>
class Vector {
public:
    Vector();

    explicit Vector(int sz);

    ~Vector();

    T pop();

    void push(T item);

private:
    T* items;
    int size;
    int last = 0;
};

#endif //INFO_SEARCH_VECTOR_H
