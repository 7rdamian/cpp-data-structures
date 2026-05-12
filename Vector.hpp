#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template <typename T>
class Vector {
private:
    int length;
    int nr_elem;
    T* values;

    void resize() {
        T* newValues = new T[length * 2];
        for (int i = 0; i < nr_elem; i++) {
            newValues[i] = values[i];
        }
        delete[] values;
        values = newValues;
        length *= 2;
    }

public:
    Vector(int initialLength = 2) {
        length = initialLength;
        nr_elem = 0;
        values = new T[length];
    }

    ~Vector() {
        delete[] values;
    }

    void insertBeg(T value) {
        if (nr_elem >= length) {
            resize(); 
        }
        for (int i = nr_elem - 1; i >= 0; i--) {
            values[i + 1] = values[i];
        }
        values[0] = value;
        nr_elem++;
    }

    void insertEnd(T value) {
        if (nr_elem >= length) {
            resize();
        }
        values[nr_elem] = value;
        nr_elem++;
    }

    bool deleteBeg() {
        if (nr_elem == 0) return false; 

        for (int i = 0; i < nr_elem - 1; i++) {
            values[i] = values[i + 1];
        }
        nr_elem--;
        return true; 
    }

    bool deleteEnd() {
        if (nr_elem == 0) return false;

        nr_elem--;
        return true;
    }

    void print() const {
        if (nr_elem == 0) {
            std::cout << "Vector is empty\n";
            return;
        }
        for (int i = 0; i < nr_elem; i++) {
            std::cout << values[i] << " ";
        }
        std::cout << "\n";
    }
    
    int search(T value) const {
        for (int i = 0; i < nr_elem; i++) {
            if (values[i] == value) return i;
        }
        return -1;
    }
};

#endif