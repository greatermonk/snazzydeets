#ifndef MAPS_HPP
#define MAPS_HPP 

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <sstream>
#include "../console_colors/colours.hpp"
using namespace colors;


template<typename T>
std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}


// ==================== EXCEPTIONS ====================
class MapException : public std::runtime_error {
public:
    explicit MapException(const std::string& msg) : std::runtime_error(msg) {}
};

class KeyNotFoundException : public MapException {
public:
    explicit KeyNotFoundException(const std::string& key) 
        : MapException("Key not found: " + key) {}
};

// ==================== HASH MAP IMPLEMENTATION ====================
template<typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<Node*> table;
    size_t mapSize;
    size_t capacity;
    const float loadFactor = 0.75f;

    size_t hashFunction(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

    void rehash() {
        size_t oldCapacity = capacity;
        capacity *= 2;
        std::vector<Node*> oldTable = table;
        table = std::vector<Node*>(capacity, nullptr);
        mapSize = 0;

        for (size_t i = 0; i < oldCapacity; ++i) {
            Node* current = oldTable[i];
            while (current) {
                insert(current->key, current->value);
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

public:
    HashMap(size_t cap = 16) : capacity(cap), mapSize(0) {
        table.resize(capacity, nullptr);
    }

    ~HashMap() {
        clear();
    }

    void insert(const K& key, const V& value) {
        if ((float)mapSize / capacity >= loadFactor) {
            rehash();
        }

        size_t index = hashFunction(key);
        Node* current = table[index];

        // Update if key exists
        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        // Insert new node
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        mapSize++;
    }

    void create_map_from_arrays(const std::vector<K>& keys, const std::vector<V>& values) {
        if (keys.size() != values.size()) {
            std::cout << RED;
            throw MapException("Arrays must have equal length");
            std::cout << RESET;
        }
        for (size_t i = 0; i < keys.size(); ++i) {
            insert(keys[i], values[i]);
        }
    }

    std::vector<K> keys() const {
        std::vector<K> result;
        for (const auto& bucket : table) {
            Node* current = bucket;
            while (current) {
                result.push_back(current->key);
                current = current->next;
            }
        }
        return result;
    }

    std::vector<V> values() const {
        std::vector<V> result;
        for (const auto& bucket : table) {
            Node* current = bucket;
            while (current) {
                result.push_back(current->value);
                current = current->next;
            }
        }
        return result;
    }

    std::vector<std::pair<K, V>> pairs() const {
        std::vector<std::pair<K, V>> result;
        for (const auto& bucket : table) {
            Node* current = bucket;
            while (current) {
                result.push_back({current->key, current->value});
                current = current->next;
            }
        }
        return result;
    }

    V& at(const K& key) {
        size_t index = hashFunction(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        throw KeyNotFoundException(std::to_string(key));
    }

    V& operator[](const K& key) {
        size_t index = hashFunction(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        // Insert with default value
        insert(key, V());
        return at(key);
    }

    void erase(const K& key) {
        size_t index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                mapSize--;
                return;
            }
            prev = current;
            current = current->next;
        }
        throw KeyNotFoundException(toString(key));
    }

    void erase(const std::vector<K>& keysToDelete) {
        for (const auto& key : keysToDelete) {
            try {
                erase(key);
            } catch (const KeyNotFoundException&) {
                // Continue deleting other keys
            }
        }
    }

    HashMap<K, V> operator+(const HashMap<K, V>& other) const {
        HashMap<K, V> result(*this);
        result.update(other);
        return result;
    }

    void update(const HashMap<K, V>& other) {
        auto otherPairs = other.pairs();
        for (const auto& p : otherPairs) {
            insert(p.first, p.second);
        }
    }

    bool find(const K& key) const {
        size_t index = hashFunction(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) return true;
            current = current->next;
        }
        return false;
    }

    bool exists(const K& key) const {
        return find(key);
    }

    bool existsValue(const V& value) const {
        for (const auto& bucket : table) {
            Node* current = bucket;
            while (current) {
                if (current->value == value) return true;
                current = current->next;
            }
        }
        return false;
    }

    void sort_by(const std::string& criterion) {
        auto pairsList = pairs();
        if (criterion == "key") {
            std::sort(pairsList.begin(), pairsList.end(),
                [](const auto& a, const auto& b)
                { 
                return a.first < b.first; 
                });
        }

        else if (criterion == "key-reverse" || criterion == "keyreverse") {
            std::sort(pairsList.begin(), pairsList.end(),
                [](const auto& a, const auto& b) { return a.first > b.first; });
        }

        else if (criterion == "value") {
            std::sort(pairsList.begin(), pairsList.end(),
                [](const auto& a, const auto& b) { return a.second < b.second; });
        }


        else if (criterion == "value-reverse" || criterion == "valuereverse") {
            std::sort(pairsList.rbegin(), pairsList.rend(),
                [](const auto& a, const auto& b) { return a.second < b.second; });
        }

        else {
              throw std::logic_error("Invalid Sorting criteria. It should be either of: key, key-reverse, value, value-reverse\n");
        }

        clear();
        for (const auto& p : pairsList) {
            insert(p.first, p.second);
        }
    }

    size_t size() const { return mapSize; }

    void clear() {
        for (auto& bucket : table) {
            Node* current = bucket;
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            bucket = nullptr;
        }
        mapSize = 0;
    }

    void display(bool use_color = false) const {
        cprint(use_color,"\n╔══════════════ HashMap ══════════════╗\n", BRIGHT_BLACK, true); 
        if (mapSize == 0) {
            cprint(use_color, "║  (empty)                           ║\n", BRIGHT_RED);
        } else {
            for (const auto& bucket : table) {
                Node* current = bucket;
                while (current) {
                    cprint(use_color, "║  ", BRIGHT_BLACK, true);
                    cprint(use_color, current->key, BRIGHT_BLUE);
                    cprint(use_color, " → ", BRIGHT_YELLOW);
                    cprint(use_color, current->value, GREEN);
                    std::cout << std::endl;
                    current = current->next;
               }
            }
        }
        std::cout << "\n";
        cprint(use_color, "╚═════════════════════════════════════╝\n", BRIGHT_BLACK);
        cprint(use_color, "Size: ");
        cprint(use_color, mapSize, BRIGHT_CYAN);
        std::cout << "\n\n";
    }
};

// ==================== TREE MAP IMPLEMENTATION ====================
template<typename K, typename V>
class TreeMap {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;
        
        Node(const K& k, const V& v) 
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    size_t mapSize;

    int height(Node* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    Node* insertNode(Node* node, const K& key, const V& value, bool& updated) {
        if (!node) {
            mapSize++;
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key, value, updated);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key, value, updated);
        } else {
            node->value = value;
            updated = true;
            return node;
        }

        return balance(node);
    }

    Node* findMin(Node* node) const {
        while (node->left) node = node->left;
        return node;
    }

    Node* eraseNode(Node* node, const K& key, bool& found) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = eraseNode(node->left, key, found);
        } else if (key > node->key) {
            node->right = eraseNode(node->right, key, found);
        } else {
            found = true;
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                mapSize--;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = eraseNode(node->right, temp->key, found);
            found = true;
        }

        return balance(node);
    }

    Node* findNode(Node* node, const K& key) const {
        if (!node) return nullptr;
        if (key < node->key) return findNode(node->left, key);
        if (key > node->key) return findNode(node->right, key);
        return node;
    }

    void inorder(Node* node, std::vector<std::pair<K, V>>& result) const {
        if (!node) return;
        inorder(node->left, result);
        result.push_back({node->key, node->value});
        inorder(node->right, result);
    }

    void destroyTree(Node* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void displayTree(Node* node, const std::string& prefix, bool isLeft, bool use_color) const {
        if (!node) return;

        std::cout << prefix;
        cprint(use_color, (isLeft ? "├── " : "└── "), BRIGHT_GREEN);
        cprint(use_color, node->key, BRIGHT_BLUE);
        cprint(use_color, " → ", YELLOW);
        cprint(use_color, node->value, GREEN);
        std::cout << "\n";

        if (node->left || node->right) {
            if (node->left) {
                displayTree(node->left, prefix + (isLeft ? "│   " : "    "), true, use_color);
            }
            if (node->right) {
                displayTree(node->right, prefix + (isLeft ? "│   " : "    "), false, use_color);
            }
        }
    }

public:
    TreeMap() : root(nullptr), mapSize(0) {}

    ~TreeMap() {
        clear();
    }

    void insert(const K& key, const V& value) {
        bool updated = false;
        root = insertNode(root, key, value, updated);
    }

    void create_map_from_arrays(const std::vector<K>& keys, const std::vector<V>& values) {
        if (keys.size() != values.size()) {
            throw MapException("Arrays must have equal length");
        }
        for (size_t i = 0; i < keys.size(); ++i) {
            insert(keys[i], values[i]);
        }
    }

    std::vector<K> keys() const {
        std::vector<std::pair<K, V>> pairsList;
        inorder(root, pairsList);
        std::vector<K> result;
        for (const auto& p : pairsList) {
            result.push_back(p.first);
        }
        return result;
    }

    std::vector<V> values() const {
        std::vector<std::pair<K, V>> pairsList;
        inorder(root, pairsList);
        std::vector<V> result;
        for (const auto& p : pairsList) {
            result.push_back(p.second);
        }
        return result;
    }

    std::vector<std::pair<K, V>> pairs() const {
        std::vector<std::pair<K, V>> result;
        inorder(root, result);
        return result;
    }

    V& at(const K& key) {
        Node* node = findNode(root, key);
        if (!node) {
            throw KeyNotFoundException(toString(key));
        }
        return node->value;
    }

    V& operator[](const K& key) {
        Node* node = findNode(root, key);
        if (!node) {
            insert(key, V());
            node = findNode(root, key);
        }
        return node->value;
    }

    void erase(const K& key) {
        bool found = false;
        root = eraseNode(root, key, found);
        if (!found) {
            throw KeyNotFoundException(toString(key));
        }
    }

    void erase(const std::vector<K>& keysToDelete) {
        for (const auto& key : keysToDelete) {
            try {
                erase(key);
            } catch (const KeyNotFoundException&) {
                // Continue deleting other keys
            }
        }
    }

    TreeMap<K, V> operator+(const TreeMap<K, V>& other) const {
        TreeMap<K, V> result(*this);
        result.update(other);
        return result;
    }

    void update(const TreeMap<K, V>& other) {
        auto otherPairs = other.pairs();
        for (const auto& p : otherPairs) {
            insert(p.first, p.second);
        }
    }

    bool find(const K& key) const {
        return findNode(root, key) != nullptr;
    }

    bool exists(const K& key) const {
        return find(key);
    }

    bool existsValue(const V& value) const {
        auto vals = values();
        return std::find(vals.begin(), vals.end(), value) != vals.end();
    }

    void sort_by(const std::string& criterion) {
        auto pairsList = pairs();
        if (criterion == "value") {
            std::sort(pairsList.begin(), pairsList.end(),
                [](const auto& a, const auto& b) { return a.second < b.second; });
            clear();
            for (const auto& p : pairsList) {
                insert(p.first, p.second);
            }
        }
        // TreeMap is already sorted by key
    }

    size_t size() const { return mapSize; }

    void clear() {
        destroyTree(root);
        root = nullptr;
        mapSize = 0;
    }

    void display(bool use_color = false) const {
        cprint(use_color, "\n╔══════════════ TreeMap (AVL) ══════════════╗\n", BRIGHT_BLACK, true);
        if (mapSize == 0) {
            cprint(use_color, "║  (empty)                                  ║\n", BRIGHT_RED);
        } else {
            cprint(use_color, "║\n", BRIGHT_BLACK, true);

            displayTree(root, "║ ", false, use_color);
        }
        cprint(use_color, "╚═══════════════════════════════════════════╝\n", BRIGHT_BLACK);
        cprint(use_color, "Size: ");
        cprint(use_color, mapSize, BRIGHT_CYAN);
        cprint(use_color, " | Height: ");
        cprint(use_color, height(root), BRIGHT_CYAN);
        std::cout << "\n\n";
    }
};

// ==================== LINKED LIST MAP IMPLEMENTATION ====================
template<typename K, typename V>
class LinkedListMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    Node* head;
    size_t mapSize;

    Node* findNode(const K& key) const {
        Node* current = head;
        while (current) {
            if (current->key == key) return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    LinkedListMap() : head(nullptr), mapSize(0) {}

    ~LinkedListMap() {
        clear();
    }

    void insert(const K& key, const V& value) {
        Node* existing = findNode(key);
        if (existing) {
            existing->value = value;
            return;
        }

        Node* newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
        mapSize++;
    }

    void create_map_from_arrays(const std::vector<K>& keys, const std::vector<V>& values) {
        if (keys.size() != values.size()) {
            throw MapException("Arrays must have equal length");
        }
        for (size_t i = 0; i < keys.size(); ++i) {
            insert(keys[i], values[i]);
        }
    }

    std::vector<K> keys() const {
        std::vector<K> result;
        Node* current = head;
        while (current) {
            result.push_back(current->key);
            current = current->next;
        }
        return result;
    }

    std::vector<V> values() const {
        std::vector<V> result;
        Node* current = head;
        while (current) {
            result.push_back(current->value);
            current = current->next;
        }
        return result;
    }

    std::vector<std::pair<K, V>> pairs() const {
        std::vector<std::pair<K, V>> result;
        Node* current = head;
        while (current) {
            result.push_back({current->key, current->value});
            current = current->next;
        }
        return result;
    }

    V& at(const K& key) {
        Node* node = findNode(key);
        if (!node) {
            throw KeyNotFoundException(toString(key));
        }
        return node->value;
    }

    V& operator[](const K& key) {
        Node* node = findNode(key);
        if (!node) {
            insert(key, V());
            node = findNode(key);
        }
        return node->value;
    }

    void erase(const K& key) {
        if (!head) {
            throw KeyNotFoundException("");
        }

        if (head->key == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            mapSize--;
            return;
        }

        Node* current = head;
        while (current->next) {
            if (current->next->key == key) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                mapSize--;
                return;
            }
            current = current->next;
        }

        throw KeyNotFoundException(toString(key));
    }

    void erase(const std::vector<K>& keysToDelete) {
        for (const auto& key : keysToDelete) {
            try {
                erase(key);
            } catch (const KeyNotFoundException&) {
                // Continue deleting other keys
            }
        }
    }

    LinkedListMap<K, V> operator+(const LinkedListMap<K, V>& other) const {
        LinkedListMap<K, V> result(*this);
        result.update(other);
        return result;
    }

    void update(const LinkedListMap<K, V>& other) {
        auto otherPairs = other.pairs();
        for (const auto& p : otherPairs) {
            insert(p.first, p.second);
        }
    }

    bool find(const K& key) const {
        return findNode(key) != nullptr;
    }

    bool exists(const K& key) const {
        return find(key);
    }

    bool existsValue(const V& value) const {
        Node* current = head;
        while (current) {
            if (current->value == value) return true;
            current = current->next;
        }
        return false;
    }

    void sort_by(const std::string& criterion) {
        auto pairsList = pairs();
        if (criterion == "key") {
            std::sort(pairsList.begin(), pairsList.end(),
                [](const auto& a, const auto& b) { return a.first < b.first; });
        } else if (criterion == "value") {
            std::sort(pairsList.begin(), pairsList.end(),
                [](const auto& a, const auto& b) { return a.second < b.second; });
        }
        clear();
        for (const auto& p : pairsList) {
            insert(p.first, p.second);
        }
    }

    size_t size() const { return mapSize; }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        mapSize = 0;
    }

    void display(bool use_color = false) const {
        cprint(use_color, "\n╔══════════════ LinkedListMap ══════════════╗\n", BRIGHT_BLACK, true);
        if (mapSize == 0) {
            cprint(use_color, "║  (empty)                                  ║\n", BRIGHT_RED);
        } else {
            Node* current = head;
            bool first = true;
            cprint(use_color, "║  ", BRIGHT_BLACK, true); 
            while (current) {
                if (!first) cprint(use_color, " → ", BRIGHT_YELLOW);
                cprint(use_color, "[", BRIGHT_GREEN);
                cprint(use_color, current->key, BRIGHT_BLUE);
                cprint(use_color, ":", YELLOW);
                cprint(use_color, current->value, GREEN);
                cprint(use_color, "]" , BRIGHT_GREEN);
                current = current->next;
                first = false;
            }
            std::cout << "\n";
            std::cout << std::endl;
        }
        cprint(use_color, "╚═══════════════════════════════════════════╝\n", BRIGHT_BLACK);
        cprint(use_color, "Size: ");
        cprint(use_color,  mapSize, BRIGHT_CYAN);
        std::cout << "\n\n";
    }
};
#endif
