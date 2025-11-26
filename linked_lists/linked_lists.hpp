#ifndef LINKED_LISTS_HPP
#define LINKED_LISTS_HPP 

#include <iostream>
#include <stdexcept>
#include <functional>
#include <string>
#include "../console_colors/colours.hpp"

using namespace colors;
// ============================================================================
// NODE STRUCTURES
// ============================================================================

template <typename T>
struct SinglyNode {
    T data;
    SinglyNode* next;
    
    SinglyNode(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
struct DoublyNode {
    T data;
    DoublyNode* prev;
    DoublyNode* next;
    
    DoublyNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

// ============================================================================
// SINGLY LINKED LIST
// ============================================================================

template <typename T>
class SinglyLinkedList {
private:
    SinglyNode<T>* head;
    size_t listSize;
    
    SinglyNode<T>* getNodeAt(size_t index) const {
        SinglyNode<T>* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }
    
    SinglyNode<T>* merge(SinglyNode<T>* left, SinglyNode<T>* right, 
                         std::function<bool(const T&, const T&)> comp) {
        if (!left) return right;
        if (!right) return left;
        
        SinglyNode<T>* result = nullptr;
        if (comp(left->data, right->data)) {
            result = left;
            result->next = merge(left->next, right, comp);
        } else {
            result = right;
            result->next = merge(left, right->next, comp);
        }
        return result;
    }
    
    SinglyNode<T>* mergeSort(SinglyNode<T>* node, 
                             std::function<bool(const T&, const T&)> comp) {
        if (!node || !node->next) return node;
        
        SinglyNode<T>* slow = node;
        SinglyNode<T>* fast = node->next;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        SinglyNode<T>* mid = slow->next;
        slow->next = nullptr;
        
        SinglyNode<T>* left = mergeSort(node, comp);
        SinglyNode<T>* right = mergeSort(mid, comp);
        
        return merge(left, right, comp);
    }

public:
    SinglyLinkedList() : head(nullptr), listSize(0) {}
    
    ~SinglyLinkedList() {
        clear();
    }
    
    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), listSize(0) {
        SinglyNode<T>* current = other.head;
        while (current) {
            addLast(current->data);
            current = current->next;
        }
    }
    
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();
            SinglyNode<T>* current = other.head;
            while (current) {
                addLast(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    void addFirst(const T& value) {
        SinglyNode<T>* newNode = new SinglyNode<T>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }
    
    void addLast(const T& value) {
        if (!head) {
            addFirst(value);
            return;
        }
        
        SinglyNode<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        
        current->next = new SinglyNode<T>(value);
        listSize++;
    }
    
    void addAt(size_t index, const T& value) {
        if (index > listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            addFirst(value);
            return;
        }
        
        SinglyNode<T>* prev = getNodeAt(index - 1);
        SinglyNode<T>* newNode = new SinglyNode<T>(value);
        newNode->next = prev->next;
        prev->next = newNode;
        listSize++;
    }
    
    T removeFirst() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        
        SinglyNode<T>* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        listSize--;
        return value;
    }
    
    T removeLast() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        
        if (!head->next) {
            return removeFirst();
        }
        
        SinglyNode<T>* current = head;
        while (current->next->next) {
            current = current->next;
        }
        
        T value = current->next->data;
        delete current->next;
        current->next = nullptr;
        listSize--;
        return value;
    }
    
    T removeAt(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            return removeFirst();
        }
        
        SinglyNode<T>* prev = getNodeAt(index - 1);
        SinglyNode<T>* toDelete = prev->next;
        T value = toDelete->data;
        prev->next = toDelete->next;
        delete toDelete;
        listSize--;
        return value;
    }
    
    bool remove(const T& value) {
        if (!head) return false;
        
        if (head->data == value) {
            removeFirst();
            return true;
        }
        
        SinglyNode<T>* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        
        if (current->next) {
            SinglyNode<T>* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
            listSize--;
            return true;
        }
        
        return false;
    }
    
    T& get(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    const T& get(size_t index) const {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    T& operator[](size_t index) {
        return get(index);
    }
    
    const T& operator[](size_t index) const {
        return get(index);
    }
    
    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }
    
    T& back() {
        if (!head) throw std::runtime_error("List is empty");
        SinglyNode<T>* current = head;
        while (current->next) current = current->next;
        return current->data;
    }
    
    int indexOf(const T& value) const {
        SinglyNode<T>* current = head;
        int index = 0;
        while (current) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        return -1;
    }
    
    int lastIndexOf(const T& value) const {
        SinglyNode<T>* current = head;
        int index = 0;
        int lastFound = -1;
        while (current) {
            if (current->data == value) lastFound = index;
            current = current->next;
            index++;
        }
        return lastFound;
    }
    
    bool contains(const T& value) const {
        return indexOf(value) != -1;
    }
    
    size_t size() const {
        return listSize;
    }
    
    bool isEmpty() const {
        return listSize == 0;
    }
    
    void clear() {
        while (head) {
            SinglyNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }
    
    void reverse() {
        SinglyNode<T>* prev = nullptr;
        SinglyNode<T>* current = head;
        SinglyNode<T>* next = nullptr;
        
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
    }
    
    void sort(bool ascending = true) {
        if (!head || !head->next) return;
        
        auto comp = ascending ? 
            [](const T& a, const T& b) { return a <= b; } :
            [](const T& a, const T& b) { return a >= b; };
        
        head = mergeSort(head, comp);
    }
    
    SinglyLinkedList operator+(const SinglyLinkedList& other) const {
        SinglyLinkedList result(*this);
        SinglyNode<T>* current = other.head;
        while (current) {
            result.addLast(current->data);
            current = current->next;
        }
        return result;
    }
    
    void merge(const SinglyLinkedList& other) {
        SinglyNode<T>* current = other.head;
        while (current) {
            addLast(current->data);
            current = current->next;
        }
    }
    
    void display(bool use_color = false) const {
      //  std::cout << "Singly Linked List\n";
        cprint(use_color, "Singly Linked List\n");
      //  std::cout << "    +---+\n";
        cprint(use_color, "    +----+\n", BRIGHT_YELLOW);
      //  std::cout << "HEAD|";
      //  std::cout << std::endl;
        cprint(use_color, "HEAD|", BRIGHT_MAGNETA, true);
        if (!head) {
      //      std::cout << "NULL| --> NULL\n";
            cprint(use_color, "NULL| --> NULL\n", RED, true);
       //     std::cout << "    +----+\n";
            cprint(use_color, "    +----+\n", BRIGHT_YELLOW);
            return;
        }
        
        SinglyNode<T>* current = head;
        bool first = true;
        while (current) {
            if (!first) cprint(use_color, "|", YELLOW);
               cprint(use_color, current->data, BRIGHT_BLUE);
               first = false;
         //   std::cout << "| --> ";
               cprint(use_color, "| --> ", YELLOW);
               current = current->next;
        }
      //  std::cout << "NULL\n";
        cprint(use_color, "NULL\n", BRIGHT_RED);
     //   std::cout << "    +---+\n";
        cprint(use_color, "    +----+\n", BRIGHT_YELLOW);
    }


    class Iterator {
    private:
        SinglyNode<T>* current;
    public:
        Iterator(SinglyNode<T>* node) : current(node) {}
        
        T& operator*() { return current->data; }
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

// ============================================================================
// DOUBLY LINKED LIST
// ============================================================================

template <typename T>
class DoublyLinkedList {
private:
    DoublyNode<T>* head;
    DoublyNode<T>* tail;
    size_t listSize;
    
    DoublyNode<T>* getNodeAt(size_t index) const {
        if (index < listSize / 2) {
            DoublyNode<T>* current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next;
            }
            return current;
        } else {
            DoublyNode<T>* current = tail;
            for (size_t i = listSize - 1; i > index; i--) {
                current = current->prev;
            }
            return current;
        }
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    
    ~DoublyLinkedList() {
        clear();
    }
    
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
        DoublyNode<T>* current = other.head;
        while (current) {
            addLast(current->data);
            current = current->next;
        }
    }
    
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            DoublyNode<T>* current = other.head;
            while (current) {
                addLast(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    void addFirst(const T& value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }
    
    void addLast(const T& value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }
    
    void addAt(size_t index, const T& value) {
        if (index > listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            addFirst(value);
            return;
        }
        
        if (index == listSize) {
            addLast(value);
            return;
        }
        
        DoublyNode<T>* current = getNodeAt(index);
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        listSize++;
    }
    
    T removeFirst() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        
        DoublyNode<T>* temp = head;
        T value = temp->data;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        delete temp;
        listSize--;
        return value;
    }
    
    T removeLast() {
        if (!tail) {
            throw std::runtime_error("List is empty");
        }
        
        DoublyNode<T>* temp = tail;
        T value = temp->data;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete temp;
        listSize--;
        return value;
    }
    
    T removeAt(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            return removeFirst();
        }
        
        if (index == listSize - 1) {
            return removeLast();
        }
        
        DoublyNode<T>* toDelete = getNodeAt(index);
        T value = toDelete->data;
        
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        
        delete toDelete;
        listSize--;
        return value;
    }
    
    bool remove(const T& value) {
        DoublyNode<T>* current = head;
        while (current) {
            if (current->data == value) {
                if (current == head) {
                    removeFirst();
                } else if (current == tail) {
                    removeLast();
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    listSize--;
                }
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    T& get(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    const T& get(size_t index) const {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    T& operator[](size_t index) {
        return get(index);
    }
    
    const T& operator[](size_t index) const {
        return get(index);
    }
    
    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }
    
    T& back() {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }
    
    int indexOf(const T& value) const {
        DoublyNode<T>* current = head;
        int index = 0;
        while (current) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        return -1;
    }
    
    int lastIndexOf(const T& value) const {
        DoublyNode<T>* current = tail;
        int index = listSize - 1;
        while (current) {
            if (current->data == value) return index;
            current = current->prev;
            index--;
        }
        return -1;
    }
    
    bool contains(const T& value) const {
        return indexOf(value) != -1;
    }
    
    size_t size() const {
        return listSize;
    }
    
    bool isEmpty() const {
        return listSize == 0;
    }
    
    void clear() {
        while (head) {
            DoublyNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        listSize = 0;
    }
    
    void reverse() {
        DoublyNode<T>* current = head;
        DoublyNode<T>* temp = nullptr;
        
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        
        if (temp) {
            tail = head;
            head = temp->prev;
        }
    }
    
    void sort(bool ascending = true) {
        if (!head || !head->next) return;
        
        bool swapped;
        do {
            swapped = false;
            DoublyNode<T>* current = head;
            while (current->next) {
                bool shouldSwap = ascending ? 
                    (current->data > current->next->data) :
                    (current->data < current->next->data);
                
                if (shouldSwap) {
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
    
    DoublyLinkedList operator+(const DoublyLinkedList& other) const {
        DoublyLinkedList result(*this);
        DoublyNode<T>* current = other.head;
        while (current) {
            result.addLast(current->data);
            current = current->next;
        }
        return result;
    }
    
    void merge(const DoublyLinkedList& other) {
        DoublyNode<T>* current = other.head;
        while (current) {
            addLast(current->data);
            current = current->next;
        }
    }
    
    void display(bool use_color = false) const {
        cprint(use_color, "Doubly Linked List:\n");
        cprint(use_color, "             +---+\n", BRIGHT_YELLOW);
        cprint(use_color, "NULL <-- HEAD|", MAGNETA);
        if (!head) {
            cprint(use_color, "NULL|\n", BRIGHT_RED);
            cprint(use_color, "             +---+", BRIGHT_YELLOW);
            cprint(use_color, " <--\n", GREEN);
            return;
        }

        DoublyNode<T>* current = head;
        bool first = true;
        while (current) {
            if (!first) cprint(use_color, "|", YELLOW);
            cprint(use_color, current->data, BRIGHT_BLUE);
            first = false;
            cprint(use_color, "| --> ", GREEN);
            current = current->next;
        }
        cprint(use_color, "NULL\n", BRIGHT_RED);
        cprint(use_color, "             +---+", BRIGHT_YELLOW);
        cprint(use_color, " <-- ", GREEN);

        current = tail;
        while (current) {
            cprint(use_color, " ");
            cprint(use_color, current->data, BRIGHT_BLUE);
            cprint(use_color, " <--", GREEN);
            current = current->prev;
        }
        std::cout << "\n";
    }


    class Iterator {
    private:
        DoublyNode<T>* current;
    public:
        Iterator(DoublyNode<T>* node) : current(node) {}
        
        T& operator*() { return current->data; }
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }
        Iterator& operator--() {
            if (current) current = current->prev;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

// ============================================================================
// CIRCULAR LINKED LIST
// ============================================================================
template <typename T>
class CircularLinkedList {
private:
    SinglyNode<T>* tail;  // Pointing to last node for O(1) front/back access
    size_t listSize;
    
    SinglyNode<T>* getNodeAt(size_t index) const {
        if (!tail) return nullptr;
        
        SinglyNode<T>* current = tail->next;  // Start from head
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

public:
    CircularLinkedList() : tail(nullptr), listSize(0) {}
    
    ~CircularLinkedList() {
        clear();
    }
    
    // Copy constructor
    CircularLinkedList(const CircularLinkedList& other) : tail(nullptr), listSize(0) {
        if (!other.tail) return;
        
        SinglyNode<T>* current = other.tail->next;
        do {
            addLast(current->data);
            current = current->next;
        } while (current != other.tail->next);
    }
    
    // Assignment operator
    CircularLinkedList& operator=(const CircularLinkedList& other) {
        if (this != &other) {
            clear();
            if (other.tail) {
                SinglyNode<T>* current = other.tail->next;
                do {
                    addLast(current->data);
                    current = current->next;
                } while (current != other.tail->next);
            }
        }
        return *this;
    }
    
    // Adding elements
    void addFirst(const T& value) {
        SinglyNode<T>* newNode = new SinglyNode<T>(value);
        
        if (!tail) {
            tail = newNode;
            newNode->next = newNode;
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
        }
        listSize++;
    }
    
    void addLast(const T& value) {
        addFirst(value);
        tail = tail->next;
    }
    
    void addAt(size_t index, const T& value) {
        if (index > listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            addFirst(value);
            return;
        }
        
        if (index == listSize) {
            addLast(value);
            return;
        }
        
        SinglyNode<T>* prev = getNodeAt(index - 1);
        SinglyNode<T>* newNode = new SinglyNode<T>(value);
        newNode->next = prev->next;
        prev->next = newNode;
        listSize++;
    }
    
    // Removing elements
    T removeFirst() {
        if (!tail) {
            throw std::runtime_error("List is empty");
        }
        
        SinglyNode<T>* head = tail->next;
        T value = head->data;
        
        if (tail == head) {
            delete tail;
            tail = nullptr;
        } else {
            tail->next = head->next;
            delete head;
        }
        
        listSize--;
        return value;
    }
    
    T removeLast() {
        if (!tail) {
            throw std::runtime_error("List is empty");
        }
        
        T value = tail->data;
        
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
        } else {
            SinglyNode<T>* current = tail->next;
            while (current->next != tail) {
                current = current->next;
            }
            current->next = tail->next;
            delete tail;
            tail = current;
        }
        
        listSize--;
        return value;
    }
    
    T removeAt(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            return removeFirst();
        }
        
        if (index == listSize - 1) {
            return removeLast();
        }
        
        SinglyNode<T>* prev = getNodeAt(index - 1);
        SinglyNode<T>* toDelete = prev->next;
        T value = toDelete->data;
        prev->next = toDelete->next;
        delete toDelete;
        listSize--;
        return value;
    }
    
    bool remove(const T& value) {
        if (!tail) return false;
        
        SinglyNode<T>* head = tail->next;
        
        if (head->data == value) {
            removeFirst();
            return true;
        }
        
        SinglyNode<T>* current = head;
        do {
            if (current->next->data == value) {
                SinglyNode<T>* toDelete = current->next;
                if (toDelete == tail) {
                    tail = current;
                }
                current->next = toDelete->next;
                delete toDelete;
                listSize--;
                return true;
            }
            current = current->next;
        } while (current != tail);
        
        return false;
    }
    
    // Accessing elements
    T& get(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    const T& get(size_t index) const {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    T& operator[](size_t index) {
        return get(index);
    }
    
    const T& operator[](size_t index) const {
        return get(index);
    }
    
    T& front() {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->next->data;
    }
    
    T& back() {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }
    
    // Searching
    int indexOf(const T& value) const {
        if (!tail) return -1;
        
        SinglyNode<T>* current = tail->next;
        int index = 0;
        do {
            if (current->data == value) return index;
            current = current->next;
            index++;
        } while (current != tail->next);
        
        return -1;
    }
    
    int lastIndexOf(const T& value) const {
        if (!tail) return -1;
        
        SinglyNode<T>* current = tail->next;
        int index = 0;
        int lastFound = -1;
        do {
            if (current->data == value) lastFound = index;
            current = current->next;
            index++;
        } while (current != tail->next);
        
        return lastFound;
    }
    
    bool contains(const T& value) const {
        return indexOf(value) != -1;
    }
    
    // Utility methods
    size_t size() const {
        return listSize;
    }
    
    bool isEmpty() const {
        return listSize == 0;
    }
    
    void clear() {
        if (!tail) return;
        
        SinglyNode<T>* head = tail->next;
        SinglyNode<T>* current = head;
        do {
            SinglyNode<T>* temp = current;
            current = current->next;
            delete temp;
        } while (current != head);
        
        tail = nullptr;
        listSize = 0;
    }
    
    void reverse() {
        if (!tail || tail->next == tail) return;
        
        SinglyNode<T>* prev = tail;
        SinglyNode<T>* current = tail->next;
        SinglyNode<T>* head = tail->next;
        SinglyNode<T>* next = nullptr;
        
        do {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        } while (current != head);
        
        tail = head;
    }
    
    void sort(bool ascending = true) {
        if (!tail || tail->next == tail) return;
        
        bool swapped;
        do {
            swapped = false;
            SinglyNode<T>* current = tail->next;
            SinglyNode<T>* next = current->next;
            
            do {
                bool shouldSwap = ascending ? 
                    (current->data > next->data) :
                    (current->data < next->data);
                
                if (shouldSwap) {
                    T temp = current->data;
                    current->data = next->data;
                    next->data = temp;
                    swapped = true;
                }
                
                current = next;
                next = next->next;
            } while (current != tail);
        } while (swapped);
    }
    
    // Merging
    CircularLinkedList operator+(const CircularLinkedList& other) const {
        CircularLinkedList result(*this);
        if (other.tail) {
            SinglyNode<T>* current = other.tail->next;
            do {
                result.addLast(current->data);
                current = current->next;
            } while (current != other.tail->next);
        }
        return result;
    }
    
    void merge(const CircularLinkedList& other) {
        if (other.tail) {
            SinglyNode<T>* current = other.tail->next;
            do {
                addLast(current->data);
                current = current->next;
            } while (current != other.tail->next);
        }
    }
    
    // Display
    void display(bool use_color = false) const {
        cprint(use_color, "Circular Linked List:\n");
        if (!tail) {
            cprint(use_color, "    +----+\n", BRIGHT_YELLOW);
            cprint(use_color, "HEAD|NULL|\n", BRIGHT_RED);
            cprint(use_color, "    +----+\n", BRIGHT_YELLOW);
            return;
        }
        
        cprint(use_color, "    +---+  ", BRIGHT_YELLOW);
        
        SinglyNode<T>* current = tail->next;
        int nodeCount = 0;
        SinglyNode<T>* temp = current;
        do {
            nodeCount++;
            temp = temp->next;
        } while (temp != tail->next);
        
        // Print top border for tail
        for (int i = 1; i < nodeCount; i++) {
            std::cout << "        ";
        }
        cprint(use_color, "+---+\n", BRIGHT_YELLOW);
        // Print nodes
        cprint(use_color, "HEAD|", BRIGHT_MAGNETA, true);
        cprint(use_color, current->data, BRIGHT_BLUE);
        cprint(use_color, "|", YELLOW);
        current = current->next;
        
        while (current != tail->next) {
            cprint(use_color, " -->", GREEN);
            cprint(use_color, " |", YELLOW);
            cprint(use_color, current->data, BRIGHT_BLUE);
            cprint(use_color, "|", YELLOW);
            current = current->next;
        }
        std::cout << "\n";
        
        // Print bottom border
        cprint(use_color, "    +---+", BRIGHT_YELLOW);
        for (int i = 1; i < nodeCount; i++) {
            std::cout << "       ";
        }
        cprint(use_color, "      +---+\n", BRIGHT_YELLOW);
        
        // Print connection line
        cprint(use_color, "      |", BRIGHT_CYAN);
        for (int i = 1; i < nodeCount; i++) {
            cprint(use_color, "---------", BRIGHT_CYAN);
        }
        cprint(use_color, "----|\n", BRIGHT_CYAN);
    }


    // Iterator class
    class Iterator {
    private:
        SinglyNode<T>* start;
        SinglyNode<T>* current;
        bool firstIteration;
    public:
        Iterator(SinglyNode<T>* node, bool isEnd = false) 
            : start(node), current(node), firstIteration(!isEnd) {}
        
        T& operator*() { return current->data; }
        Iterator& operator++() {
            if (current) {
                current = current->next;
                if (current == start) {
                    firstIteration = false;
                }
            }
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            if (!current && !other.current) return false;
            if (!current || !other.current) return true;
            if (!firstIteration && current == start) return false;
            return current != other.current || firstIteration != other.firstIteration;
        }
    };
    
    Iterator begin() { return Iterator(tail ? tail->next : nullptr); }
    Iterator end() { return Iterator(tail ? tail->next : nullptr, true); }
};



// ============================================================================
// CIRCULAR DOUBLY LINKED LIST
// ============================================================================

template <typename T>
class CircularDoublyLinkedList {
private:
    DoublyNode<T>* head;
    size_t listSize;
    
    DoublyNode<T>* getNodeAt(size_t index) const {
        if (!head) return nullptr;
        
        DoublyNode<T>* current = head;
        if (index < listSize / 2) {
            for (size_t i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            for (size_t i = listSize; i > index; i--) {
                current = current->prev;
            }
        }
        return current;
    }

public:
    CircularDoublyLinkedList() : head(nullptr), listSize(0) {}
    
    ~CircularDoublyLinkedList() {
        clear();
    }
    
    CircularDoublyLinkedList(const CircularDoublyLinkedList& other) : head(nullptr), listSize(0) {
        if (!other.head) return;
        
        DoublyNode<T>* current = other.head;
        do {
            addLast(current->data);
            current = current->next;
        } while (current != other.head);
    }
    
    CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList& other) {
        if (this != &other) {
            clear();
            if (other.head) {
                DoublyNode<T>* current = other.head;
                do {
                    addLast(current->data);
                    current = current->next;
                } while (current != other.head);
            }
        }
        return *this;
    }
    
    void addFirst(const T& value) {
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        
        if (!head) {
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            DoublyNode<T>* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
        listSize++;
    }
    
    void addLast(const T& value) {
        if (!head) {
            addFirst(value);
            return;
        }
        
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        DoublyNode<T>* tail = head->prev;
        
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        listSize++;
    }
    
    void addAt(size_t index, const T& value) {
        if (index > listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            addFirst(value);
            return;
        }
        
        if (index == listSize) {
            addLast(value);
            return;
        }
        
        DoublyNode<T>* current = getNodeAt(index);
        DoublyNode<T>* newNode = new DoublyNode<T>(value);
        
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        listSize++;
    }
    
    T removeFirst() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        
        DoublyNode<T>* temp = head;
        T value = temp->data;
        
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            DoublyNode<T>* tail = head->prev;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
        
        listSize--;
        return value;
    }
    
    T removeLast() {
        if (!head) {
            throw std::runtime_error("List is empty");
        }
        
        if (head->next == head) {
            return removeFirst();
        }
        
        DoublyNode<T>* tail = head->prev;
        T value = tail->data;
        
        tail->prev->next = head;
        head->prev = tail->prev;
        delete tail;
        
        listSize--;
        return value;
    }
    
    T removeAt(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            return removeFirst();
        }
        
        if (index == listSize - 1) {
            return removeLast();
        }
        
        DoublyNode<T>* toDelete = getNodeAt(index);
        T value = toDelete->data;
        
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        
        delete toDelete;
        listSize--;
        return value;
    }
    
    bool remove(const T& value) {
        if (!head) return false;
        
        DoublyNode<T>* current = head;
        do {
            if (current->data == value) {
                if (current == head && head->next == head) {
                    delete head;
                    head = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    if (current == head) {
                        head = head->next;
                    }
                    delete current;
                }
                listSize--;
                return true;
            }
            current = current->next;
        } while (current != head);
        
        return false;
    }
    
    T& get(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    const T& get(size_t index) const {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }
        return getNodeAt(index)->data;
    }
    
    T& operator[](size_t index) {
        return get(index);
    }
    
    const T& operator[](size_t index) const {
        return get(index);
    }
    
    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }
    
    T& back() {
        if (!head) throw std::runtime_error("List is empty");
        return head->prev->data;
    }
    
    int indexOf(const T& value) const {
        if (!head) return -1;
        
        DoublyNode<T>* current = head;
        int index = 0;
        do {
            if (current->data == value) return index;
            current = current->next;
            index++;
        } while (current != head);
        
        return -1;
    }
    
    int lastIndexOf(const T& value) const {
        if (!head) return -1;
        
        DoublyNode<T>* current = head;
        int index = 0;
        int lastFound = -1;
        do {
            if (current->data == value) lastFound = index;
            current = current->next;
            index++;
        } while (current != head);
        
        return lastFound;
    }
    
    bool contains(const T& value) const {
        return indexOf(value) != -1;
    }
    
    size_t size() const {
        return listSize;
    }
    
    bool isEmpty() const {
        return listSize == 0;
    }
    
    void clear() {
        if (!head) return;
        
        DoublyNode<T>* current = head;
        do {
            DoublyNode<T>* temp = current;
            current = current->next;
            delete temp;
        } while (current != head);
        
        head = nullptr;
        listSize = 0;
    }
    
    void reverse() {
        if (!head || head->next == head) return;
        
        DoublyNode<T>* current = head;
        do {
            DoublyNode<T>* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        } while (current != head);
        
        head = head->next;
    }
    
    void sort(bool ascending = true) {
        if (!head || head->next == head) return;
        
        bool swapped;
        do {
            swapped = false;
            DoublyNode<T>* current = head;
            
            do {
                bool shouldSwap = ascending ? 
                    (current->data > current->next->data) :
                    (current->data < current->next->data);
                
                if (current->next != head && shouldSwap) {
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                
                current = current->next;
            } while (current->next != head);
        } while (swapped);
    }
    
    CircularDoublyLinkedList operator+(const CircularDoublyLinkedList& other) const {
        CircularDoublyLinkedList result(*this);
        if (other.head) {
            DoublyNode<T>* current = other.head;
            do {
                result.addLast(current->data);
                current = current->next;
            } while (current != other.head);
        }
        return result;
    }
    
    void merge(const CircularDoublyLinkedList& other) {
        if (other.head) {
            DoublyNode<T>* current = other.head;
            do {
                addLast(current->data);
                current = current->next;
            } while (current != other.head);
        }
    }
    
    void display(bool use_color = false) const {
        std::cout << "Doubly Circular Linked List\n";
        
        if (!head) {
            cprint(use_color, "    +----+\n", BRIGHT_YELLOW);
            cprint(use_color, "HEAD|NULL\n", MAGNETA, true);
            cprint(use_color, "    +----+\n", BRIGHT_YELLOW);
            return;
        }
        
        std::cout << "\n";
        cprint(use_color, "    +---+ ", BRIGHT_YELLOW);
        
        DoublyNode<T>* current = head;
        int nodeCount = 0;
        DoublyNode<T>* temp = current;
        do {
            nodeCount++;
            temp = temp->next;
        } while (temp != head);
        
        // Print top border for tail
        for (int i = 1; i < nodeCount; i++) {
            std::cout << "       ";
        }
        cprint(use_color, "+---+\n", BRIGHT_YELLOW);
        
        // Print forward direction
        cprint(use_color, "HEAD|", BRIGHT_MAGNETA, true);
        cprint(use_color, current->data, BRIGHT_BLUE);
        cprint(use_color, "|", YELLOW);
        current = current->next;
        
        while (current != head) {
            cprint(use_color, " --> |", BRIGHT_GREEN);
            cprint(use_color, current->data, BRIGHT_BLUE);
            cprint(use_color, "|", YELLOW);
            current = current->next;
        }
        std::cout << "\n";
        
        // Print bottom border
        cprint(use_color, "    +---+", BRIGHT_YELLOW);
        for (int i = 1; i < nodeCount; i++) {
            std::cout << "        ";
        }
        cprint(use_color, "+---+\n", BRIGHT_YELLOW);
        
        // Print connection line
        std::cout << "      |";
        for (int i = 1; i < nodeCount; i++) {
            cprint(use_color, "-------", BRIGHT_CYAN);
        }
        cprint(use_color, "------|\n", BRIGHT_CYAN);
    }

    class Iterator {
    private:
        DoublyNode<T>* start;
        DoublyNode<T>* current;
        bool firstIteration;
    public:
        Iterator(DoublyNode<T>* node, bool isEnd = false) 
            : start(node), current(node), firstIteration(!isEnd) {}
        
        T& operator*() { return current->data; }
        Iterator& operator++() {
            if (current) {
                current = current->next;
                if (current == start) {
                    firstIteration = false;
                }
            }
            return *this;
        }
        Iterator& operator--() {
            if (current) {
                current = current->prev;
                if (current == start) {
                    firstIteration = false;
                }
            }
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            if (!current && !other.current) return false;
            if (!current || !other.current) return true;
            if (!firstIteration && current == start) return false;
            return current != other.current || firstIteration != other.firstIteration;
        }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(head, true); }
};
#endif
