#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T value;
        Node* next;
        
        Node(T val) : value(val), next(nullptr) {}
    };

    Node* topNode;
    int nrElem;

public:
    Stack() {
        topNode = nullptr;
        nrElem = 0;
    }

    ~Stack() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    bool emptyStack() const {
        return topNode == nullptr;
    }

    void push(T newValue) {
        Node* elem = new Node(newValue);
        elem->next = topNode;
        topNode = elem;
        nrElem++;
    }

    bool pop() {
        if (emptyStack()) return false;

        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
        nrElem--;
        return true;
    }

    bool peek(T& value) const {
        if (emptyStack()) return false;

        value = topNode->value;
        return true;
    }

    void printStack() const {
        Node* tmp = topNode;
        while (tmp != nullptr) {
            std::cout << tmp->value << " ";
            tmp = tmp->next;
        }
        std::cout << "\n";
    }

    int getNrElem() const {
        return nrElem;
    }

    bool contains(T target) const {
        Node* tmp = topNode;
        while (tmp != nullptr) {
            if (tmp->value == target) return true;
            tmp = tmp->next;
        }
        return false;
    }

    void sortStack() {
        if (emptyStack() || topNode->next == nullptr) return;

        Stack<T> tempStack;
        
        while (!emptyStack()) {
            T tempValue;
            peek(tempValue);
            pop();

            T topTempValue;
            while (!tempStack.emptyStack() && tempStack.peek(topTempValue) && topTempValue > tempValue) {
                push(topTempValue);
                tempStack.pop();
            }
            tempStack.push(tempValue);
        }

        while (!tempStack.emptyStack()) {
            T tempValue;
            tempStack.peek(tempValue);
            tempStack.pop();
            push(tempValue);
        }
    }
};

#endif