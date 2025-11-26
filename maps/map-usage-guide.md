# Map Data Structures - Complete Usage Guide

## Table of Contents
1. [Overview](#overview)
2. [Map Types](#map-types)
3. [Installation & Compilation](#installation--compilation)
4. [Basic Operations](#basic-operations)
5. [Advanced Features](#advanced-features)
6. [Performance Characteristics](#performance-characteristics)
7. [Complete API Reference](#complete-api-reference)
8. [Examples & Use Cases](#examples--use-cases)
9. [Error Handling](#error-handling)
10. [Best Practices](#best-practices)

---

## Overview

This library provides three different map implementations in C++:

- **HashMap** - Hash table with separate chaining for fast lookups
- **TreeMap** - Self-balancing AVL tree that maintains sorted order
- **LinkedListMap** - Simple linked list implementation

All maps are template-based and support any comparable key-value types.

---

## Map Types

### HashMap (Hash Table)
```cpp
HashMap<int, std::string> map;
```
- **Best for**: Fast lookups, insertions, and deletions
- **Time Complexity**: O(1) average case
- **Order**: Unordered
- **Use when**: Performance is critical and order doesn't matter

### TreeMap (AVL Tree)
```cpp
TreeMap<int, std::string> map;
```
- **Best for**: Maintaining sorted order, range queries
- **Time Complexity**: O(log n) guaranteed
- **Order**: Sorted by keys
- **Use when**: You need sorted data or balanced performance

### LinkedListMap
```cpp
LinkedListMap<std::string, int> map;
```
- **Best for**: Small datasets, simple implementation
- **Time Complexity**: O(n)
- **Order**: Insertion order (can be sorted)
- **Use when**: Simplicity matters or dataset is small

---

## Installation & Compilation

### Requirements
- C++11 or later
- Standard C++ libraries

### Compilation
```bash
# Basic compilation
g++ -std=c++11 map_implementation.cpp -o map_program

# With optimizations
g++ -std=c++11 -O2 map_implementation.cpp -o map_program

# Run the program
./map_program
```

---

## Basic Operations

### 1. Creating Maps

```cpp
// Create empty maps
HashMap<int, std::string> hashMap;
TreeMap<std::string, double> treeMap;
LinkedListMap<char, int> listMap;

// Maps with different types
HashMap<std::string, std::vector<int>> complexMap;
TreeMap<double, std::string> floatKeyMap;
```

### 2. Inserting Elements

#### Method 1: Using `insert()`
```cpp
HashMap<int, std::string> map;

// Insert key-value pairs
map.insert(1, "Apple");
map.insert(2, "Banana");
map.insert(3, "Cherry");

// Update existing key
map.insert(1, "Apricot");  // Overwrites "Apple"
```

#### Method 2: Using `operator[]`
```cpp
map[4] = "Date";
map[5] = "Elderberry";

// Creates new entry if key doesn't exist
map[10] = "Zebra";
```

#### Method 3: Creating from Arrays
```cpp
std::vector<int> keys = {10, 20, 30, 40};
std::vector<std::string> values = {"Ten", "Twenty", "Thirty", "Forty"};

HashMap<int, std::string> map;
map.create_map_from_arrays(keys, values);
```

### 3. Accessing Elements

#### Using `at()` (with bounds checking)
```cpp
try {
    std::string value = map.at(1);
    std::cout << "Value: " << value << std::endl;
} catch (const KeyNotFoundException& e) {
    std::cerr << e.what() << std::endl;
}
```

#### Using `operator[]` (creates if doesn't exist)
```cpp
// Safe access - creates entry with default value if missing
std::string value = map[1];

// Modify value
map[1] = "New Value";
```

### 4. Removing Elements

#### Remove single element
```cpp
try {
    map.erase(3);  // Remove key 3
} catch (const KeyNotFoundException& e) {
    std::cerr << "Key not found!" << std::endl;
}
```

#### Remove multiple elements
```cpp
std::vector<int> keysToRemove = {1, 3, 5, 7};
map.erase(keysToRemove);  // Silently skips non-existent keys
```

### 5. Checking Existence

```cpp
// Check if key exists
if (map.exists(5)) {
    std::cout << "Key 5 exists!" << std::endl;
}

// Alternative using find()
if (map.find(5)) {
    std::cout << "Found key 5!" << std::endl;
}

// Check if value exists
if (map.existsValue("Apple")) {
    std::cout << "Value 'Apple' exists!" << std::endl;
}
```

### 6. Getting Keys, Values, and Pairs

```cpp
// Get all keys
std::vector<int> allKeys = map.keys();
for (const auto& key : allKeys) {
    std::cout << key << " ";
}

// Get all values
std::vector<std::string> allValues = map.values();
for (const auto& val : allValues) {
    std::cout << val << " ";
}

// Get all key-value pairs
auto allPairs = map.pairs();
for (const auto& pair : allPairs) {
    std::cout << pair.first << " => " << pair.second << std::endl;
}
```

### 7. Display Map

```cpp
// Beautiful ASCII visualization
map.display();

// Output for HashMap:
// ╔══════════════ HashMap ══════════════╗
// ║  1 → Apple
// ║  2 → Banana
// ║  3 → Cherry
// ╚═════════════════════════════════════╝
// Size: 3
```

### 8. Other Operations

```cpp
// Get size
size_t count = map.size();

// Clear all elements
map.clear();

// Check if empty
if (map.size() == 0) {
    std::cout << "Map is empty" << std::endl;
}
```

---

## Advanced Features

### 1. Merging Maps

#### Using `operator+`
```cpp
HashMap<int, std::string> map1;
map1.insert(1, "One");
map1.insert(2, "Two");

HashMap<int, std::string> map2;
map2.insert(3, "Three");
map2.insert(4, "Four");

// Merge and create new map
HashMap<int, std::string> merged = map1 + map2;
merged.display();
```

#### Using `update()`
```cpp
// Merge in-place
map1.update(map2);  // map2's elements are added to map1

// Handles key conflicts (later value overwrites)
HashMap<int, std::string> mapA;
mapA.insert(1, "First");

HashMap<int, std::string> mapB;
mapB.insert(1, "Updated");  // This will overwrite

mapA.update(mapB);
std::cout << mapA.at(1);  // Output: "Updated"
```

### 2. Sorting Maps

```cpp
HashMap<int, std::string> map;
map.insert(5, "Five");
map.insert(1, "One");
map.insert(3, "Three");

// Sort by key
map.sort_by("key");
map.display();  // Shows: 1, 3, 5

// Sort by value
map.sort_by("value");
map.display();  // Shows sorted by values
```

**Note**: TreeMap is always sorted by key automatically!

### 3. TreeMap Specific Features

```cpp
TreeMap<int, std::string> tree;
tree.insert(50, "Fifty");
tree.insert(30, "Thirty");
tree.insert(70, "Seventy");
tree.insert(20, "Twenty");

// Display shows balanced tree structure
tree.display();

// Output:
// ╔══════════════ TreeMap (AVL) ══════════════╗
// ║
// ║ └── 50 → Fifty
// ║     ├── 30 → Thirty
// ║     │   └── 20 → Twenty
// ║     └── 70 → Seventy
// ╚═══════════════════════════════════════════╝
// Size: 4 | Height: 3
```

### 4. Complex Data Types

```cpp
// String keys with vector values
HashMap<std::string, std::vector<int>> studentGrades;
studentGrades["Alice"] = {95, 87, 92};
studentGrades["Bob"] = {78, 85, 90};

// Accessing complex values
auto aliceGrades = studentGrades.at("Alice");
for (int grade : aliceGrades) {
    std::cout << grade << " ";
}

// Custom struct as value
struct Person {
    std::string name;
    int age;
};

TreeMap<int, Person> employees;
employees.insert(101, {"John Doe", 30});
employees.insert(102, {"Jane Smith", 25});
```

---

## Performance Characteristics

| Operation | HashMap | TreeMap | LinkedListMap |
|-----------|---------|---------|---------------|
| Insert | O(1) avg | O(log n) | O(1) |
| Search | O(1) avg | O(log n) | O(n) |
| Delete | O(1) avg | O(log n) | O(n) |
| Access | O(1) avg | O(log n) | O(n) |
| Sorted Order | No | Yes | No (unless sorted) |
| Memory | Medium | Medium | Low |
| Best Use | Fast lookup | Sorted data | Small datasets |

### Space Complexity
- **HashMap**: O(n) + overhead for buckets
- **TreeMap**: O(n) + node pointers
- **LinkedListMap**: O(n) minimal overhead

---

## Complete API Reference

### Constructor & Destructor
```cpp
HashMap<K, V>()              // Create empty map (default capacity: 16)
HashMap<K, V>(size_t cap)    // Create with specific capacity
~HashMap<K, V>()             // Destructor (automatic cleanup)
```

### Insertion Methods
```cpp
void insert(const K& key, const V& value)
void create_map_from_arrays(const vector<K>& keys, const vector<V>& values)
V& operator[](const K& key)
```

### Retrieval Methods
```cpp
V& at(const K& key)                          // Throws if not found
vector<K> keys() const
vector<V> values() const
vector<pair<K, V>> pairs() const
```

### Search Methods
```cpp
bool find(const K& key) const
bool exists(const K& key) const
bool existsValue(const V& value) const
```

### Deletion Methods
```cpp
void erase(const K& key)                     // Throws if not found
void erase(const vector<K>& keysArray)       // Silent on missing keys
void clear()
```

### Merge/Update Methods
```cpp
HashMap<K, V> operator+(const HashMap<K, V>& other) const
void update(const HashMap<K, V>& other)
```

### Utility Methods
```cpp
void sort_by(const string& criterion)        // "key" or "value"
size_t size() const
void display() const
```

---

## Examples & Use Cases

### Example 1: Student Grade Management
```cpp
#include <iostream>
#include <vector>
#include "map_implementation.cpp"

int main() {
    HashMap<std::string, double> studentGrades;
    
    // Add students
    studentGrades.insert("Alice", 95.5);
    studentGrades.insert("Bob", 87.3);
    studentGrades.insert("Charlie", 92.0);
    
    // Update a grade
    studentGrades["Bob"] = 89.5;
    
    // Check if student exists
    if (studentGrades.exists("Alice")) {
        std::cout << "Alice's grade: " << studentGrades.at("Alice") << std::endl;
    }
    
    // Display all grades
    studentGrades.display();
    
    // Sort by grade (value)
    studentGrades.sort_by("value");
    std::cout << "\nSorted by grade:\n";
    studentGrades.display();
    
    return 0;
}
```

### Example 2: Frequency Counter
```cpp
void countWordFrequency(const std::vector<std::string>& words) {
    HashMap<std::string, int> frequency;
    
    // Count frequencies
    for (const auto& word : words) {
        if (frequency.exists(word)) {
            frequency[word]++;
        } else {
            frequency[word] = 1;
        }
    }
    
    // Display results
    frequency.sort_by("value");
    frequency.display();
}

int main() {
    std::vector<std::string> text = {
        "hello", "world", "hello", "cpp", "world", "hello"
    };
    
    countWordFrequency(text);
    // Output: hello → 3, world → 2, cpp → 1
    
    return 0;
}
```

### Example 3: Configuration Manager
```cpp
class ConfigManager {
private:
    TreeMap<std::string, std::string> config;
    
public:
    void loadDefaults() {
        config.insert("host", "localhost");
        config.insert("port", "8080");
        config.insert("timeout", "30");
        config.insert("debug", "false");
    }
    
    void set(const std::string& key, const std::string& value) {
        config[key] = value;
    }
    
    std::string get(const std::string& key) {
        try {
            return config.at(key);
        } catch (const KeyNotFoundException& e) {
            return "";
        }
    }
    
    void displayAll() {
        config.display();  // Shows sorted by key
    }
};

int main() {
    ConfigManager cm;
    cm.loadDefaults();
    cm.set("port", "9090");
    cm.displayAll();
    
    return 0;
}
```

### Example 4: Cache Implementation
```cpp
template<typename K, typename V>
class LRUCache {
private:
    LinkedListMap<K, V> cache;
    size_t maxSize;
    
public:
    LRUCache(size_t size) : maxSize(size) {}
    
    void put(const K& key, const V& value) {
        if (cache.exists(key)) {
            cache.erase(key);
        } else if (cache.size() >= maxSize) {
            // Remove oldest (first in linked list)
            auto keys = cache.keys();
            if (!keys.empty()) {
                cache.erase(keys[0]);
            }
        }
        cache.insert(key, value);
    }
    
    V get(const K& key) {
        if (!cache.exists(key)) {
            throw KeyNotFoundException("Cache miss");
        }
        V value = cache.at(key);
        // Move to front (remove and reinsert)
        cache.erase(key);
        cache.insert(key, value);
        return value;
    }
    
    void display() {
        cache.display();
    }
};
```

### Example 5: Phone Book
```cpp
class PhoneBook {
private:
    TreeMap<std::string, std::string> contacts;
    
public:
    void addContact(const std::string& name, const std::string& number) {
        contacts[name] = number;
        std::cout << "Added: " << name << std::endl;
    }
    
    void removeContact(const std::string& name) {
        try {
            contacts.erase(name);
            std::cout << "Removed: " << name << std::endl;
        } catch (const KeyNotFoundException& e) {
            std::cout << "Contact not found!" << std::endl;
        }
    }
    
    std::string lookupNumber(const std::string& name) {
        try {
            return contacts.at(name);
        } catch (const KeyNotFoundException& e) {
            return "Not found";
        }
    }
    
    void listAll() {
        std::cout << "\n=== Phone Book (Alphabetically Sorted) ===\n";
        contacts.display();
    }
    
    std::vector<std::string> searchByNumber(const std::string& number) {
        std::vector<std::string> results;
        auto allPairs = contacts.pairs();
        for (const auto& pair : allPairs) {
            if (pair.second == number) {
                results.push_back(pair.first);
            }
        }
        return results;
    }
};
```

---

## Error Handling

### Exception Types

```cpp
// Base exception
try {
    // Map operations
} catch (const MapException& e) {
    std::cerr << "Map error: " << e.what() << std::endl;
}

// Key not found exception
try {
    auto value = map.at(999);
} catch (const KeyNotFoundException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

// Array length mismatch
try {
    std::vector<int> keys = {1, 2, 3};
    std::vector<std::string> values = {1, 2};  // Wrong size!
    map.create_map_from_arrays(keys, values);
} catch (const MapException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

### Safe Usage Patterns

```cpp
// Pattern 1: Check before access
if (map.exists(key)) {
    auto value = map.at(key);
    // Use value safely
}

// Pattern 2: Use operator[] for default values
auto value = map[key];  // Creates entry if missing

// Pattern 3: Try-catch for error handling
try {
    map.erase(key);
    std::cout << "Successfully deleted" << std::endl;
} catch (const KeyNotFoundException& e) {
    std::cout << "Key doesn't exist" << std::endl;
}

// Pattern 4: Batch operations with error tolerance
std::vector<int> keysToDelete = {1, 2, 999, 3};
map.erase(keysToDelete);  // Silently skips non-existent keys
```

---

## Best Practices

### 1. Choose the Right Map Type

```cpp
// Use HashMap for:
// - Fast lookups in large datasets
// - When order doesn't matter
// - General-purpose key-value storage
HashMap<int, std::string> fastLookup;

// Use TreeMap for:
// - Sorted data requirements
// - Range queries
// - Maintaining order automatically
TreeMap<std::string, int> sortedData;

// Use LinkedListMap for:
// - Small datasets (<100 elements)
// - When simplicity is key
// - Preserving insertion order
LinkedListMap<char, int> simpleMap;
```

### 2. Memory Management

```cpp
// Clear maps when done
map.clear();

// Use local scope
{
    HashMap<int, int> tempMap;
    // Use map
}  // Automatically destroyed here

// For large maps, consider reserve capacity
HashMap<int, std::string> largeMap(1000);  // Pre-allocate
```

### 3. Error Handling

```cpp
// Always handle potential errors
try {
    auto value = map.at(key);
    processValue(value);
} catch (const KeyNotFoundException& e) {
    handleError(e);
}

// Or check existence first
if (map.exists(key)) {
    processValue(map.at(key));
}
```

### 4. Performance Tips

```cpp
// Batch insertions are faster
std::vector<int> keys = {1, 2, 3, 4, 5};
std::vector<std::string> vals = {"a", "b", "c", "d", "e"};
map.create_map_from_arrays(keys, vals);  // Better than loop

// Use references when iterating
for (const auto& pair : map.pairs()) {
    // Avoids copying
    std::cout << pair.first << ": " << pair.second << std::endl;
}

// Reserve capacity for HashMap if size is known
HashMap<int, std::string> map(expectedSize * 2);
```

### 5. Type Safety

```cpp
// Use consistent types
HashMap<int, std::string> map;
map.insert(1, "One");         // ✓ Correct
// map.insert("1", "One");    // ✗ Compiler error

// For mixed types, use std::variant or std::any
HashMap<std::string, std::any> flexibleMap;
```

---

## Troubleshooting

### Common Issues

**Issue**: Compilation error with custom types
```cpp
// Solution: Ensure type has operator<< for toString()
struct MyType {
    int value;
    friend std::ostream& operator<<(std::ostream& os, const MyType& mt) {
        os << mt.value;
        return os;
    }
};
```

**Issue**: TreeMap requires comparable keys
```cpp
// Solution: Define operator< for custom types
struct CustomKey {
    int id;
    bool operator<(const CustomKey& other) const {
        return id < other.id;
    }
};
```

**Issue**: HashMap requires hashable keys
```cpp
// Solution: Specialize std::hash for custom types
namespace std {
    template<>
    struct hash<CustomKey> {
        size_t operator()(const CustomKey& k) const {
            return hash<int>()(k.id);
        }
    };
}
```

---

## Conclusion

This map library provides flexible, efficient, and easy-to-use data structures for various use cases. Choose the right map type based on your needs, handle errors appropriately, and follow best practices for optimal performance.

For more examples and updates, refer to the source code comments and test cases.