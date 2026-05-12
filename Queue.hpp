#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T value;
        int priority;
        Node* next;
        
        Node(T val, int prio = 0) : value(val), priority(prio), next(nullptr) {}
    };

    Node* frontNode;
    Node* endNode;
    int nrElem;

public:
    Queue() {
        frontNode = nullptr;
        endNode = nullptr;
        nrElem = 0;
    }

    ~Queue() {
        while (frontNode != nullptr) {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }

    bool emptyQueue() const {
        return frontNode == nullptr;
    }

    void enqueue(T value) {
        Node* elem = new Node(value);
        
        if (emptyQueue()) {
            frontNode = elem;
            endNode = elem;
        } else {
            endNode->next = elem;
            endNode = elem;
        }
        nrElem++;
    }

    bool dequeue(T& value) {
        if (emptyQueue()) return false;

        Node* tmp = frontNode;
        value = tmp->value;
        frontNode = frontNode->next;
        
        if (frontNode == nullptr) {
            endNode = nullptr;
        }
        
        delete tmp;
        nrElem--;
        return true;
    }

    bool peek(T& value) const {
        if (emptyQueue()) return false;

        value = frontNode->value;
        return true;
    }

    void print() const {
        Node* tmp = frontNode;
        while (tmp != nullptr) {
            std::cout << tmp->value << " ";
            tmp = tmp->next;
        }
        std::cout << "\n";
    }

    int search(T value) const {
        Node* tmp = frontNode;
        int pos = 0;
        
        while (tmp != nullptr) {
            if (tmp->value == value) return pos;
            tmp = tmp->next;
            pos++;
        }
        return -1;
    }

    void deleteDuplicates() {
        if (emptyQueue() || frontNode->next == nullptr) return;

        Node* current = frontNode;
        while (current != nullptr) {
            Node* runner = current;
            while (runner->next != nullptr) {
                if (runner->next->value == current->value) {
                    Node* duplicate = runner->next;
                    runner->next = runner->next->next;
                    
                    if (duplicate == endNode) {
                        endNode = runner;
                    }
                    
                    delete duplicate;
                    nrElem--;
                } else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    void enqueueWithPriority(T value, int priority) {
        Node* elem = new Node(value, priority);

        if (emptyQueue() || priority > frontNode->priority) {
            elem->next = frontNode;
            frontNode = elem;
            if (endNode == nullptr) {
                endNode = elem;
            }
        } else {
            Node* tmp = frontNode;
            while (tmp->next != nullptr && tmp->next->priority >= priority) {
                tmp = tmp->next;
            }
            elem->next = tmp->next;
            tmp->next = elem;
            
            if (elem->next == nullptr) {
                endNode = elem;
            }
        }
        nrElem++;
    }

    void printQueuePriority() const {
        Node* tmp = frontNode;
        while (tmp != nullptr) {
            std::cout << "[" << tmp->value << ", p:" << tmp->priority << "] ";
            tmp = tmp->next;
        }
        std::cout << "\n";
    }

    bool reverse() {
        if (emptyQueue() || frontNode->next == nullptr) return false;

        Node* prev = nullptr;
        Node* current = frontNode;
        Node* next = nullptr;

        endNode = frontNode; 

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        frontNode = prev;
        return true;
    }

    bool sort() {
        if (emptyQueue() || frontNode->next == nullptr) return false;

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = frontNode;

            while (ptr1->next != lptr) {
                if (ptr1->value > ptr1->next->value) {
                    T tempValue = ptr1->value;
                    int tempPriority = ptr1->priority;
                    
                    ptr1->value = ptr1->next->value;
                    ptr1->priority = ptr1->next->priority;
                    
                    ptr1->next->value = tempValue;
                    ptr1->next->priority = tempPriority;
                    
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        return true;
    }
};

#endif