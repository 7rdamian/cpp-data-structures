#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <iostream>

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T value;
        Node* next;
        
        Node(T val) : value(val), next(nullptr) {}
    };

    Node* head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    ~SinglyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    void insertBeg(T val) {
        Node* elem = new Node(val);
        if (head == nullptr) {
            head = elem;
        } else {
            elem->next = head;
            head = elem;
        }
    }

    bool insertMid(T val, int pos) {
        if (pos == 0) {
            insertBeg(val);
            return true;
        }

        Node* tmp = head;
        int i = 0;
        while (tmp != nullptr && i < pos - 1) {
            tmp = tmp->next;
            i++;
        }

        if (tmp == nullptr) return false;

        Node* elem = new Node(val);
        elem->next = tmp->next;
        tmp->next = elem;

        return true;
    }

    void insertEnd(T val) {
        Node* elem = new Node(val);
        if (head == nullptr) {
            head = elem;
            return;
        }

        Node* tmp = head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = elem;
    }

    bool deleteBeg() {
        if (head == nullptr) return false;

        Node* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    bool deleteEnd() {
        if (head == nullptr) return false;

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return true;
        }

        Node* tmp = head;
        while (tmp->next->next != nullptr) {
            tmp = tmp->next;
        }

        delete tmp->next;
        tmp->next = nullptr;
        return true;
    }

    bool deleteMid(T val) {
        if (head == nullptr) return false;

        if (head->value == val) {
            return deleteBeg();
        }

        Node* tmp = head;
        while (tmp->next != nullptr && tmp->next->value != val) {
            tmp = tmp->next;
        }

        if (tmp->next == nullptr) return false;

        Node* nodeToDelete = tmp->next;
        tmp->next = tmp->next->next;
        delete nodeToDelete;
        return true;
    }

    void print() const {
        if (head == nullptr) {
            std::cout << "List is empty\n";
            return;
        }
        Node* tmp = head;
        while (tmp != nullptr) {
            std::cout << tmp->value << " ";
            tmp = tmp->next;
        }
        std::cout << "\n";
    }

    bool max(T& maxVal) const {
        if (head == nullptr) return false;

        maxVal = head->value;
        Node* tmp = head->next;

        while (tmp != nullptr) {
            if (tmp->value > maxVal) {
                maxVal = tmp->value;
            }
            tmp = tmp->next;
        }
        return true;
    }

    bool min(T& minVal) const {
        if (head == nullptr) return false;

        minVal = head->value;
        Node* tmp = head->next;

        while (tmp != nullptr) {
            if (tmp->value < minVal) {
                minVal = tmp->value;
            }
            tmp = tmp->next;
        }
        return true;
    }

    int sortList() {
        if (head == nullptr) return 1;
        if (head->next == nullptr) return 2;

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->value > ptr1->next->value) {
                    T temp = ptr1->value;
                    ptr1->value = ptr1->next->value;
                    ptr1->next->value = temp;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        return 0;
    }

    int search(T val) const {
        Node* tmp = head;
        int pos = 0;
        
        while (tmp != nullptr) {
            if (tmp->value == val) return pos;
            tmp = tmp->next;
            pos++;
        }
        return -1;
    }
};

#endif