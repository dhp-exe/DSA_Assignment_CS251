# CO2003 - Data Structures and Algorithms - Assignment 2
## Implementing Search Mechanisms in VectorStore Using Tree Data Structures

This project is an assignment for the Ho Chi Minh City University of Technology's Data Structures and Algorithms (CO2003) course. The goal is to implement a `VectorStore` class that uses tree-based data structures to efficiently store, manage, and query multidimensional vectors.

---

## Project Overview

The `VectorStore` implementation uses two coordinated self-balancing binary search trees to manage vector data:

1.  **Primary Index (AVL Tree)**: An `AVLTree` is used as the primary data store. It organizes `VectorRecord` objects based on their **Euclidean distance to a central reference vector**. This structure ensures logarithmic time complexity for insertion, deletion, and search operations and allows for efficient distance-based range queries.

2.  **Secondary Index (Red-Black Tree)**: A `RedBlackTree` is used as a secondary index that sorts vectors by their **Euclidean norm**. This index serves as a pre-filtering mechanism to accelerate top-k nearest neighbor searches by quickly selecting candidate vectors with similar magnitudes, reducing the number of expensive distance calculations.

---

## Core Components

* `VectorStore.h`: Header file containing all class definitions. **This is one of the two files to be modified and submitted**.
* `VectorStore.cpp`: Implementation file for the methods of the classes defined in `VectorStore.h`. **This is the second file to be modified and submitted**.
* `main.h`: The main header file containing standard library includes, custom exception classes (`invalid_metric`, `invalid_k_value`), and utility includes. **This file must not be modified**.
* `main.cpp`: The main driver file used for testing the `VectorStore` implementation.
* `utils.h`: A utility file, provided by the assignment.

### Classes to Implement

* **`AVLTree<K, T>`**: A template-based implementation of a self-balancing AVL Tree.
* **`RedBlackTree<K, T>`**: A template-based implementation of a self-balancing Red-Black Tree.
* **`VectorRecord`**: A data structure to hold vector information, including an ID, the original raw text, and the vector data itself.
* **`VectorStore`**: The main class that manages the AVL and Red-Black trees and implements all search and data management logic.

---

## Build & Run

### Compilation

You must use the following `g++` command to compile the project, as specified in the assignment requirements:

```bash
g++ -o main main.cpp VectorStore.cpp -I -std=c++17