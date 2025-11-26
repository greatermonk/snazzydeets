# Linked List Implementation - Usage Guide

## Table of Contents
1. [Overview](#overview)
2. [Compilation](#compilation)
3. [List Types](#list-types)
4. [Common Methods](#common-methods)
5. [Usage Examples](#usage-examples)
6. [Performance Analysis](#performance-analysis)
7. [Memory Management](#memory-management)

---

## Overview

This implementation provides four complete linked list data structures in C++:

- **Singly Linked List** - Each node points to the next node
- **Doubly Linked List** - Each node points to both next and previous nodes
- **Circular Linked List** - Singly linked list where tail connects back to head
- **Circular Doubly Linked List** - Doubly linked list with circular connections

All implementations are:
- **Template-based** - Work with any data type
- **Memory-safe** - Proper destructors and copy constructors
- **Optimized** - Fast algorithms for common operations
- **Exception-safe** - Proper error handling

---

## Compilation

### Basic Compilation
```bash
g++ -std=c++11 -o linked_lists linked_lists.cpp
./linked_lists
```

### With Optimizations
```bash
g++ -std=c++11 -O2 -Wall -Wextra -o linked_lists linked_lists.cpp
./linked_lists
```

### Debug Mode
```bash
g++ -std=c++11 -g -o linked_lists_debug linked_lists.cpp
gdb ./linked_lists_debug
```

---

## List Types

### 1. Singly Linked List

```cpp
SinglyLinkedList<int> list;
```

**Structure:**
```
HEAD|5| --> |10| --> |15| --> NULL
```

**Features:**
- O(1) insertion/removal at head
- O(n) insertion/removal at tail
- O(n) access by index
- Merge sort for sorting

### 2. Doubly Linked List

```cpp
DoublyLinkedList<std::string> list;
```

**Structure:**
```
NULL <-- HEAD|Alice| --> |Bob| --> |Charlie| --> NULL
```

**Features:**
- O(1) insertion/removal at both ends
- Bidirectional traversal
- Optimized access from nearest end
- O(n/2) average access time

### 3. Circular Linked List

```cpp
CircularLinkedList<double> list;
```

**Structure:**
```
     +----+           +----+
HEAD|50| --> |100| --> |300|
     +----+           +----+
      |---------------------|
```

**Features:**
- No NULL pointers
- Continuous traversal
- O(1) insertion at both ends (using tail pointer)

### 4. Circular Doubly Linked List

```cpp
CircularDoublyLinkedList<float> list;
```

**Structure:**
```
     +----+           +----+
HEAD|1.5| --> |2.5| --> |3.5|
     +----+           +----+
      |---------------------|
```

**Features:**
- Bidirectional circular traversal
- Most flexible implementation
- Efficient operations at both ends

---

## Common Methods

### Adding Elements

| Method | Description | Time Complexity |
|--------|-------------|-----------------|
| `addFirst(value)` | Add element at the beginning | O(1) |
| `addLast(value)` | Add element at the end | O(1) - O(n)* |
| `addAt(index, value)` | Add element at specific index | O(n) |

*O(1) for doubly and circular lists, O(n) for singly list

**Example:**
```cpp
SinglyLinkedList<int> list;
list.addFirst(10);      // List: 10
list.addLast(20);       // List: 10, 20
list.addAt(1, 15);      // List: 10, 15, 20
```

### Removing Elements

| Method | Description | Time Complexity |
|--------|-------------|-----------------|
| `removeFirst()` | Remove and return first element | O(1) |
| `removeLast()` | Remove and return last element | O(1) - O(n)* |
| `removeAt(index)` | Remove element at specific index | O(n) |
| `remove(value)` | Remove first occurrence of value | O(n) |

*O(1) for doubly lists, O(n) for singly lists

**Example:**
```cpp
int value = list.removeFirst();  // Removes and returns first element
list.removeLast();               // Removes last element
list.removeAt(2);                // Removes element at index 2
bool removed = list.remove(15);  // Removes value 15, returns true if found
```

### Accessing Elements

| Method | Description | Time Complexity |
|--------|-------------|-----------------|
| `get(index)` | Get element at index | O(n) |
| `operator[](index)` | Array-style access | O(n) |
| `front()` | Get first element | O(1) |
| `back()` | Get last element | O(1) - O(n)* |

*O(1) for doubly lists, O(n) for singly lists

**Example:**
```cpp
int val = list.get(2);        // Get element at index 2
int first = list.front();     // Get first element
int last = list.back();       // Get last element
list[1] = 100;                // Set element at index 1
```

### Searching Elements

| Method | Description | Time Complexity |
|--------|-------------|-----------------|
| `indexOf(value)` | Find first index of value | O(n) |
| `lastIndexOf(value)` | Find last index of value | O(n) |
| `contains(value)` | Check if value exists | O(n) |

**Example:**
```cpp
int index = list.indexOf(20);        // Returns index or -1
int lastIdx = list.lastIndexOf(20);  // Returns last index or -1
bool exists = list.contains(20);     // Returns true/false
```

### Utility Methods

| Method | Description | Time Complexity |
|--------|-------------|-----------------|
| `size()` | Get number of elements | O(1) |
| `isEmpty()` | Check if list is empty | O(1) |
| `clear()` | Remove all elements | O(n) |
| `reverse()` | Reverse the list | O(n) |
| `sort(ascending)` | Sort the list | O(n log n) or O(n²)* |
| `display()` | Display list with ASCII art | O(n) |

*O(n log n) for singly list (merge sort), O(n²) for others (bubble sort)

**Example:**
```cpp
size_t len = list.size();        // Get size
bool empty = list.isEmpty();     // Check if empty
list.reverse();                  // Reverse list
list.sort();                     // Sort ascending
list.sort(false);                // Sort descending
list.clear();                    // Clear all elements
list.display();                  // Print list
```

### Merging Lists

| Method | Description | Time Complexity |
|--------|-------------|-----------------|
| `operator+(other)` | Create merged copy | O(n + m) |
| `merge(other)` | Merge other list into this | O(m) |

**Example:**
```cpp
SinglyLinkedList<int> list1, list2;
list1.addLast(1);
list1.addLast(2);
list2.addLast(3);
list2.addLast(4);

// Create new merged list
SinglyLinkedList<int> merged = list1 + list2;  // [1, 2, 3, 4]

// Merge into existing list
list1.merge(list2);  // list1 becomes [1, 2, 3, 4]
```

### Iterator Support

All lists support range-based for loops:

```cpp
SinglyLinkedList<int> list;
list.addLast(10);
list.addLast(20);
list.addLast(30);

for (auto& value : list) {
    std::cout << value << " ";
}
// Output: 10 20 30
```

---

## Usage Examples

### Example 1: Basic Operations

```cpp
#include "linked_lists.cpp"

int main() {
    // Create a singly linked list of integers
    SinglyLinkedList<int> numbers;
    
    // Add elements
    numbers.addLast(10);
    numbers.addLast(20);
    numbers.addLast(30);
    numbers.addFirst(5);
    
    // Display
    numbers.display();
    // Output: HEAD|5| --> |10| --> |20| --> |30| --> NULL
    
    // Access elements
    std::cout << "First: " << numbers.front() << std::endl;  // 5
    std::cout << "Last: " << numbers.back() << std::endl;    // 30
    std::cout << "At index 2: " << numbers[2] << std::endl;  // 20
    
    // Search
    std::cout << "Index of 20: " << numbers.indexOf(20) << std::endl;  // 2
    std::cout << "Contains 15: " << numbers.contains(15) << std::endl; // 0
    
    // Remove
    numbers.removeFirst();
    numbers.display();
    // Output: HEAD|10| --> |20| --> |30| --> NULL
    
    return 0;
}
```

### Example 2: Working with Strings

```cpp
int main() {
    DoublyLinkedList<std::string> names;
    
    names.addLast("Alice");
    names.addLast("Bob");
    names.addLast("Charlie");
    names.addFirst("Zara");
    
    names.display();
    
    // Sort alphabetically
    names.sort();
    names.display();
    
    // Find and remove
    if (names.contains("Bob")) {
        names.remove("Bob");
        std::cout << "Bob removed!\n";
    }
    
    names.display();
    
    return 0;
}
```

### Example 3: Custom Data Types

```cpp
struct Student {
    std::string name;
    int age;
    double gpa;
    
    bool operator<(const Student& other) const {
        return gpa < other.gpa;
    }
    
    bool operator>(const Student& other) const {
        return gpa > other.gpa;
    }
    
    bool operator<=(const Student& other) const {
        return gpa <= other.gpa;
    }
    
    bool operator>=(const Student& other) const {
        return gpa >= other.gpa;
    }
    
    bool operator==(const Student& other) const {
        return name == other.name && age == other.age;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        return os << s.name << "(" << s.gpa << ")";
    }
};

int main() {
    SinglyLinkedList<Student> students;
    
    students.addLast({"Alice", 20, 3.8});
    students.addLast({"Bob", 22, 3.5});
    students.addLast({"Charlie", 21, 3.9});
    
    students.display();
    
    // Sort by GPA
    students.sort();
    students.display();
    
    return 0;
}
```

### Example 4: Merging Lists

```cpp
int main() {
    SinglyLinkedList<int> list1;
    list1.addLast(1);
    list1.addLast(3);
    list1.addLast(5);
    
    SinglyLinkedList<int> list2;
    list2.addLast(2);
    list2.addLast(4);
    list2.addLast(6);
    
    // Method 1: Using + operator (creates new list)
    SinglyLinkedList<int> merged = list1 + list2;
    std::cout << "Merged list:\n";
    merged.display();
    merged.sort();
    std::cout << "After sorting:\n";
    merged.display();
    
    // Method 2: Using merge() (modifies list1)
    SinglyLinkedList<int> list3;
    list3.addLast(7);
    list3.addLast(8);
    merged.merge(list3);
    std::cout << "After merging list3:\n";
    merged.display();
    
    return 0;
}
```

### Example 5: Circular List Applications

```cpp
// Round-robin scheduling simulator
int main() {
    CircularLinkedList<std::string> processes;
    
    processes.addLast("Process A");
    processes.addLast("Process B");
    processes.addLast("Process C");
    processes.addLast("Process D");
    
    processes.display();
    
    std::cout << "\nRound-robin execution:\n";
    int cycles = 3;
    for (int i = 0; i < cycles * processes.size(); i++) {
        std::cout << "Executing: " << processes[i % processes.size()] << std::endl;
    }
    
    return 0;
}
```

---

## Performance Analysis

### Time Complexity Comparison

| Operation | Singly | Doubly | Circular | Circular Doubly |
|-----------|--------|--------|----------|-----------------|
| addFirst() | O(1) | O(1) | O(1) | O(1) |
| addLast() | O(n) | O(1) | O(1) | O(1) |
| addAt(i) | O(n) | O(n) | O(n) | O(n) |
| removeFirst() | O(1) | O(1) | O(1) | O(1) |
| removeLast() | O(n) | O(1) | O(n) | O(1) |
| removeAt(i) | O(n) | O(n) | O(n) | O(n) |
| get(i) | O(n) | O(n/2)* | O(n) | O(n/2)* |
| indexOf() | O(n) | O(n) | O(n) | O(n) |
| reverse() | O(n) | O(n) | O(n) | O(n) |
| sort() | O(n log n) | O(n²) | O(n²) | O(n²) |

*Optimized to search from nearest end

### Space Complexity

| List Type | Space per Node | Additional Space |
|-----------|----------------|------------------|
| Singly | Data + 1 pointer | Head pointer + size |
| Doubly | Data + 2 pointers | Head + Tail pointers + size |
| Circular | Data + 1 pointer | Tail pointer + size |
| Circular Doubly | Data + 2 pointers | Head pointer + size |

---

## Memory Management

### Automatic Memory Management

All implementations handle memory automatically:

```cpp
{
    SinglyLinkedList<int> list;
    list.addLast(10);
    list.addLast(20);
    // Memory is automatically freed when list goes out of scope
}
```

### Copy Operations

```cpp
// Copy constructor
SinglyLinkedList<int> list1;
list1.addLast(10);
SinglyLinkedList<int> list2 = list1;  // Deep copy

// Assignment operator
SinglyLinkedList<int> list3;
list3 = list1;  // Deep copy
```

### Exception Safety

All methods that can fail throw exceptions:

```cpp
try {
    SinglyLinkedList<int> list;
    list.removeFirst();  // Throws std::runtime_error: "List is empty"
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

try {
    SinglyLinkedList<int> list;
    list.addLast(10);
    int val = list.get(5);  // Throws std::out_of_range: "Index out of range"
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

---

## Best Practices

### 1. Choose the Right List Type

- **Singly Linked List**: When you only need forward traversal and minimal memory
- **Doubly Linked List**: When you need bidirectional traversal or frequent removals
- **Circular Linked List**: For round-robin algorithms or continuous traversal
- **Circular Doubly Linked List**: For complex navigation patterns

### 2. Prefer addFirst() for Singly Lists

```cpp
// Efficient: O(1)
SinglyLinkedList<int> list;
list.addFirst(10);

// Less efficient: O(n)
list.addLast(10);
```

### 3. Use Doubly Lists for Frequent Back Operations

```cpp
// Efficient with doubly list: O(1)
DoublyLinkedList<int> list;
list.addLast(10);
list.removeLast();
list.back();
```

### 4. Clear Lists When Done

```cpp
SinglyLinkedList<int> list;
// ... use list ...
list.clear();  // Explicitly free memory if needed
```

### 5. Use Range-Based Loops

```cpp
// Preferred
for (const auto& item : list) {
    std::cout << item << " ";
}

// Instead of
for (size_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << " ";  // O(n²) total!
}
```

---

## Common Pitfalls

### 1. Modifying During Iteration

```cpp
// DON'T DO THIS
for (auto& item : list) {
    if (item == 20) {
        list.remove(item);  // Undefined behavior!
    }
}

// DO THIS INSTEAD
for (size_t i = 0; i < list.size(); ) {
    if (list[i] == 20) {
        list.removeAt(i);
    } else {
        i++;
    }
}
```

### 2. Accessing Empty Lists

```cpp
SinglyLinkedList<int> list;
// list.front();  // Throws exception!

// Check first
if (!list.isEmpty()) {
    int val = list.front();
}
```

### 3. Index Out of Bounds

```cpp
SinglyLinkedList<int> list;
list.addLast(10);
// list.get(5);  // Throws exception!

// Check size first
if (index < list.size()) {
    int val = list.get(index);
}
```

---

## Advanced Topics

### Custom Comparators for Sorting

The `sort()` method uses `operator<=` and `operator>=` for comparison. Ensure your custom types implement these operators.

### Thread Safety

These implementations are **not thread-safe**. For concurrent access, use external synchronization:

```cpp
#include <mutex>

std::mutex listMutex;
SinglyLinkedList<int> sharedList;

// Thread 1
{
    std::lock_guard<std::mutex> lock(listMutex);
    sharedList.addLast(10);
}

// Thread 2
{
    std::lock_guard<std::mutex> lock(listMutex);
    int val = sharedList.front();
}
```

---

## Conclusion

This linked list implementation provides robust, efficient, and easy-to-use data structures for various use cases. Choose the appropriate list type based on your specific requirements, and follow best practices for optimal performance.

For questions or issues, refer to the source code comments or test cases in the main implementation file.