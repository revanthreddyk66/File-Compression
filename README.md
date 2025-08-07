# File-Compression
# Huffman Coding Algorithm in C++

This project is a C++ implementation of the classic **Huffman coding algorithm**, a fundamental method for lossless data compression. It's a powerful demonstration of data structures and greedy algorithms, built from scratch using modern C++ practices.

---

## 🚀 Core Features

* **Algorithm Implementation**: Implements the complete Huffman coding workflow: calculating character frequencies, building the optimal encoding tree, and generating prefix-free codes.
* **Modern C++ Memory Management**: Uses **`std::shared_ptr`** for safe, automatic memory management of the Huffman tree, preventing any memory leaks.
* **Core Data Structures**: Leverages key data structures to build the algorithm:
    * **Priority Queue (Min-Heap)**: To efficiently build the Huffman tree.
    * **Binary Tree**: The Huffman tree itself, which is traversed for encoding and decoding.
    * **HashMap (`unordered_map`)**: To store character frequencies and the final codes.
* **Lossless Compression Demo**: The program takes sample text, compresses it, and then decompresses it back to the original to prove **100% data integrity**.

---

## 🛠️ Tech Stack

* **Language**: C++17
* **Core Concepts**: Greedy Algorithms, Data Structures, Modern C++ Memory Management
* **Build System**: `make`
