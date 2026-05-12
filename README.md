# C++ Template Data Structures

A comprehensive collection of fundamental data structures implemented from scratch in C++. This project serves as a library of header-only templates, demonstrating manual memory management, pointer manipulation, and the implementation of core computer science algorithms without relying on the C++ Standard Template Library (STL) for container logic.

## Key Features

* **Binary Search Tree**: An implementation supporting insertion, search, and a three-case deletion algorithm. It includes recursive implementations for Inorder, Preorder, and Postorder traversals, as well as tree height calculation.
* **Doubly & Singly Linked Lists**: Flexible list structures featuring insertion and deletion at the beginning, end, or specific midpoints. Includes utility functions for finding minimum/maximum values, removing duplicates, and sorting.
* **Queue**: A standard FIFO (First-In-First-Out) structure extended with Priority Queue functionality (enqueue with priority), a reversal algorithm, and duplicate removal.
* **Stack**: A LIFO (Last-In-First-Out) structure that includes a `sortStack` method, which organizes elements using a temporary stack.
* **Vector**: A custom implementation of a dynamic array that features automated resizing (capacity doubling) when the underlying buffer is full.

## Tech Stack

* **Language**: C++
* **Architecture**: Header-only Template Library
* **Concepts**: Template Programming, Manual Memory Management (Pointers, Heap Allocation), Recursion, and Sorting Algorithms.

## How to Use

Since this is a header-only library, simply include the desired header file in your project:

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/cpp-data-structures.git
    ```

2.  **Include the header in your C++ code**:
    ```cpp
    #include "BinaryTree.hpp"
    #include "Queue.hpp"

    int main() {
        // Example with Binary Search Tree
        BinaryTree<int> myTree;
        myTree.insert(10);
        myTree.insert(5);
        myTree.inorder(); // Output: 5 10
    }
    ```

3.  **Compile with a C++ compiler**:
    ```bash
    g++ main.cpp -o my_program
    ```

## What I Learned

This project was an exercise in understanding the "magic" behind the high-level containers used in modern software development. By implementing these from scratch, I learned:

* **Memory Safety**: Managing the lifecycle of nodes using `new` and `delete` to prevent memory leaks, especially during complex operations like the three-case node deletion in a Binary Search Tree.
* **Generic Programming**: Leveraging C++ Templates to write reusable code that functions with any data type.
* **Algorithmic Logic**: Implementing various traversal methods and specialized sorting logic (such as sorting a stack using only stack operations) to improve visualization of data flow and optimization of recursive processes.
