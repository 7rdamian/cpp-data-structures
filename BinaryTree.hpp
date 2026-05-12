#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node(T val) : key(val), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int nr_elem;

    void caseOne(Node*& rootRef, Node* parent, Node* tmp) {
        if (parent == nullptr) rootRef = nullptr;
        else if (parent->right == tmp) parent->right = nullptr;
        else parent->left = nullptr;
        delete tmp;
    }

    void caseTwo(Node*& rootRef, Node* parent, Node* tmp) {
        Node* child = tmp->left != nullptr ? tmp->left : tmp->right;

        if (parent == nullptr) rootRef = child;
        else if (parent->left == tmp) parent->left = child;
        else parent->right = child;

        delete tmp;
    }

    void caseThree(Node*& rootRef, Node* parent, Node* tmp) {
        Node* tmp1 = tmp->left;
        Node* predParent = tmp;

        while (tmp1->right != nullptr) {
            predParent = tmp1;
            tmp1 = tmp1->right;
        }

        tmp->key = tmp1->key;

        if (predParent == tmp)
            predParent->left = tmp1->left;
        else
            predParent->right = tmp1->left;

        delete tmp1;
    }

    void inorderHelper(Node* currentNode) const {
        if (currentNode == nullptr) return;
        inorderHelper(currentNode->left);
        std::cout << currentNode->key << " ";
        inorderHelper(currentNode->right);
    }

    void preorderHelper(Node* currentNode) const {
        if (currentNode == nullptr) return;
        std::cout << currentNode->key << " ";
        preorderHelper(currentNode->left);
        preorderHelper(currentNode->right);
    }

    void postorderHelper(Node* currentNode) const {
        if (currentNode == nullptr) return;
        postorderHelper(currentNode->left);
        postorderHelper(currentNode->right);
        std::cout << currentNode->key << " ";
    }

    Node* searchHelper(Node* currentNode, T key) const {
        if (currentNode == nullptr || currentNode->key == key)
            return currentNode;

        if (key < currentNode->key)
            return searchHelper(currentNode->left, key);
        else
            return searchHelper(currentNode->right, key);
    }

    void clearTreeHelper(Node* currentNode) {
        if (currentNode == nullptr) return;
        destroyTreeHelper(currentNode->left);
        destroyTreeHelper(currentNode->right);
        delete currentNode;
    }

    int heightHelper(Node* currentNode) const {
        if (currentNode == nullptr) {
            return -1; 
        }

        int heightLeft = heightHelper(currentNode->left);  
        int heightRight = heightHelper(currentNode->right); 

        if (heightLeft > heightRight) {
            return 1 + heightLeft;
        }
        else {
            return 1 + heightRight;
        }
    }

public:
    BinaryTree() {
        root = nullptr;
        nr_elem = 0;
    }

    ~BinaryTree() {
        destroyTreeHelper(root);
    }

    void insert(T key) {
        Node* newElem = new Node(key);
        Node* parent = nullptr;

        if (root == nullptr) {
            root = newElem;
            nr_elem++;
            return;
        }
        else {
            Node* tmp = root;
            while (tmp != nullptr) {
                parent = tmp;
                if (key < tmp->key) {
                    tmp = tmp->left;
                }
                else {
                    if (key > tmp->key) {
                        tmp = tmp->right;
                    }
                    else {
                        std::cout << "error - duplicate key\n";
                        delete newElem;
                        return;
                    }
                }
            }
        }

        if (key < parent->key) parent->left = newElem;
        else parent->right = newElem;

        nr_elem++;
    }

    void erase(T erasedKey) {
        if (root == nullptr) {
            std::cout << "error - empty tree";
            return;
        }

        Node* tmp = root;
        Node* parent = nullptr;
        while (tmp != nullptr && erasedKey != tmp->key) {
            parent = tmp;
            if (erasedKey < tmp->key) tmp = tmp->left;
            else tmp = tmp->right;
        }

        if (tmp == nullptr) {
            std::cout << "eroare - nodul nu exista";
            return;
        }
        else if (tmp->left == nullptr && tmp->right == nullptr)
            caseOne(root, parent, tmp);
        else if (tmp->left == nullptr || tmp->right == nullptr)
            caseTwo(root, parent, tmp);
        else 
            caseThree(root, parent, tmp);

        nr_elem--;
    }

    void update(T oldKey, T newKey) {
        if (searchHelper(root, newKey)) {
            std::cout << "error - new key already exists\n";
            return;
        }

        if (!searchHelper(root, oldKey)) {
            std::cout << "error - old key not found\n";
            return;
        }

        erase(oldKey);
        insert(newKey);
    }

    bool search(T key) const {
        return searchHelper(root, key) != nullptr;
    }

    void inorder() const {
        inorderHelper(root);
        std::cout << "\n";
    }

    void preorder() const {
        preorderHelper(root);
        std::cout << "\n";
    }

    void postorder() const {
        postorderHelper(root);
        std::cout << "\n";
    }

    int height() const {
        return heightHelper(root);
    }

    void clear() {
        clearTreeHelper(root);
        root = nullptr;
        nr_elem = 0;
    }
}

#endif