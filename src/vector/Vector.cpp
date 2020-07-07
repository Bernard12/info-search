//
// Created by ivan on 07.07.2020.
//

#include "Vector.h"

template<typename T>
Vector<T>::Vector() {
    size = 16;
    items = new T[size];
}

template<typename T>
Vector<T>::Vector(int sz) {
    size = sz;
    items = new T[size];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] items;
}

template<typename T>
T Vector<T>::pop() {
    return nullptr;
}

template<typename T>
void Vector<T>::push(T item) {
    if (last == size - 1) {
        // need to resize
    }
    items[last++] = item;
}


