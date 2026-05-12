#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        
        Node(T val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int nr_elem;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        nr_elem = 0;
    }

    ~DoublyLinkedList() {
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
        nr_elem++;

        if (head == nullptr) {
            head = elem;
            tail = elem;
        } else {
            elem->next = head;
            head->prev = elem;
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
        elem->prev = tmp;

        if (tmp->next != nullptr) {
            tmp->next->prev = elem;
        } else {
            tail = elem;
        }
        
        tmp->next = elem;
        nr_elem++;
        return true;
    }

    void insertEnd(T val) {
        Node* elem = new Node(val);
        nr_elem++;

        if (head == nullptr) {
            head = elem;
            tail = elem;
        } else {
            elem->prev = tail;
            tail->next = elem;
            tail = elem;
        }
    }

    bool deleteBeg() {
        if (head == nullptr) return false;

        Node* tmp = head;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        delete tmp;
        nr_elem--;
        return true;
    }

    bool deleteEnd() {
        if (tail == nullptr) return false;

        Node* tmp = tail;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete tmp;
        nr_elem--;
        return true;
    }

    bool deleteMid(T val) {
        if (head == nullptr) return false;

        if (head->value == val) {
            return deleteBeg();
        }

        if (tail->value == val) {
            return deleteEnd();
        }

        Node* tmp = head;
        while (tmp != nullptr && tmp->value != val) {
            tmp = tmp->next;
        }

        if (tmp == nullptr) return false;

        tmp->prev->next = tmp->next;
        if (tmp->next != nullptr) {
            tmp->next->prev = tmp->prev;
        }

        delete tmp;
        nr_elem--;
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

    DoublyLinkedList<T>* odd() const {
        DoublyLinkedList<T>* newList = new DoublyLinkedList<T>();
        Node* tmp = head;

        while (tmp != nullptr) {
            if (tmp->value % 2 != 0) {
                newList->insertEnd(tmp->value);
            }
            tmp = tmp->next;
        }
        return newList;
    }

    int sortList(int direction) {
        if (head == nullptr) return 1;
        if (head->next == nullptr) return 2;

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                bool condition = (direction == 0) ? (ptr1->value > ptr1->next->value) : (ptr1->value < ptr1->next->value);
                
                if (condition) {
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

    void deleteDuplicates() {
        if (head == nullptr || head->next == nullptr) return;

        Node* current = head;
        while (current != nullptr) {
            Node* runner = current->next;
            while (runner != nullptr) {
                if (runner->value == current->value) {
                    Node* duplicate = runner;
                    runner->prev->next = runner->next;
                    
                    if (runner->next != nullptr) {
                        runner->next->prev = runner->prev;
                    } else {
                        tail = runner->prev;
                    }
                    
                    runner = runner->next;
                    delete duplicate;
                    nr_elem--;
                } else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
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

    int getSize() const {
        return nr_elem;
    }
};

#endif