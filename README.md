# CO2003 - Data Structures and Algorithms - Assignment 2
## Implementing Search Mechanisms in VectorStore Using Tree Data Structures

[cite_start]This project is an assignment for the Ho Chi Minh City University of Technology's Data Structures and Algorithms (CO2003) course[cite: 2, 4]. [cite_start]The goal is to implement a `VectorStore` class that uses tree-based data structures to efficiently store, manage, and query multidimensional vectors[cite: 19].

---

## Project Overview

[cite_start]The `VectorStore` implementation uses two coordinated self-balancing binary search trees to manage vector data[cite: 23]:

1.  [cite_start]**Primary Index (AVL Tree)**: An `AVLTree` is used as the primary data store[cite: 20]. [cite_start]It organizes `VectorRecord` objects based on their **Euclidean distance to a central reference vector**[cite: 20]. [cite_start]This structure ensures logarithmic time complexity for insertion, deletion, and search operations and allows for efficient distance-based range queries[cite: 20].

2.  [cite_start]**Secondary Index (Red-Black Tree)**: A `RedBlackTree` is used as a secondary index that sorts vectors by their **Euclidean norm**[cite: 21, 304]. [cite_start]This index serves as a pre-filtering mechanism to accelerate top-k nearest neighbor searches by quickly selecting candidate vectors with similar magnitudes, reducing the number of expensive distance calculations[cite: 22, 305].

---

## Core Components

* `VectorStore.h`: Header file containing all class definitions. [cite_start]**This is one of the two files to be modified and submitted**.
* `VectorStore.cpp`: Implementation file for the methods of the classes defined in `VectorStore.h`. [cite_start]**This is the second file to be modified and submitted**[cite: 568, 585].
* [cite_start]`main.h`: The main header file containing standard library includes, custom exception classes (`invalid_metric`, `invalid_k_value`), and utility includes[cite: 569]. [cite_start]**This file must not be modified**[cite: 569].
* `main.cpp`: The main driver file used for testing the `VectorStore` implementation.
* `utils.h`: A utility file, provided by the assignment.

### Classes to Implement

* **`AVLTree<K, T>`**: A template-based implementation of a self-balancing AVL Tree.
* **`RedBlackTree<K, T>`**: A template-based implementation of a self-balancing Red-Black Tree.
* [cite_start]**`VectorRecord`**: A data structure to hold vector information, including an ID, the original raw text, and the vector data itself[cite: 325].
* **`VectorStore`**: The main class that manages the AVL and Red-Black trees and implements all search and data management logic.

---

## Build & Run

### Compilation

[cite_start]You must use the following `g++` command to compile the project, as specified in the assignment requirements[cite: 570, 571]:

```bash
g++ -o main main.cpp VectorStore.cpp -I -std=c++17