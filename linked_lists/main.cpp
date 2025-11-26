#include<iostream>
#include "linked_lists.hpp"


void testSinglyLinkedList() {
    std::cout << "\n========== TESTING SINGLY LINKED LIST ==========\n";
    
    SinglyLinkedList<int> list;
    
    list.addFirst(10);
    list.addLast(20);
    list.addLast(30);
    list.addFirst(5);
    list.addAt(2, 15);
    
    std::cout << "\nAfter adding elements (5, 10, 15, 20, 30):\n";
    list.display(true);
    std::cout << "Size: " << list.size() << std::endl;
    
    std::cout << "\nAccessing elements:\n";
    std::cout << "Element at index 2: " << list[2] << std::endl;
    std::cout << "Front: " << list.front() << ", Back: " << list.back() << std::endl;
    
    std::cout << "\nSearching:\n";
    std::cout << "Index of 15: " << list.indexOf(15) << std::endl;
    std::cout << "Contains 20: " << (list.contains(20) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 100: " << (list.contains(100) ? "Yes" : "No") << std::endl;
    
    std::cout << "\nRemoving first element: " << list.removeFirst() << std::endl;
    list.display(true);
    
    list.reverse();
    std::cout << "\nAfter reversing:\n";
    list.display(true);
    
    list.sort();
    std::cout << "\nAfter sorting (ascending):\n";
    list.display(true);
    
    SinglyLinkedList<int> list2;
    list2.addLast(40);
    list2.addLast(50);
    
    std::cout << "\nSecond list:\n";
    list2.display(true);
    
    SinglyLinkedList<int> merged = list + list2;
    std::cout << "\nMerged list (using + operator):\n";
    merged.display(true);
    
    std::cout << "\nIterating through list: ";
    for (auto val : list) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void testDoublyLinkedList() {
    std::cout << "\n========== TESTING DOUBLY LINKED LIST ==========\n";
    
    DoublyLinkedList<std::string> list;
    
    list.addLast("Alice");
    list.addLast("Bob");
    list.addLast("Charlie");
    list.addFirst("Zara");
    list.addAt(2, "Mike");
    
    std::cout << "\nAfter adding elements:\n";
    list.display(true);
    std::cout << "Size: " << list.size() << std::endl;
    
    std::cout << "\nFront: " << list.front() << ", Back: " << list.back() << std::endl;
    
    std::cout << "\nSearching:\n";
    std::cout << "Index of 'Mike': " << list.indexOf("Mike") << std::endl;
    std::cout << "Last index of 'Bob': " << list.lastIndexOf("Bob") << std::endl;
    
    list.removeAt(1);
    std::cout << "\nAfter removing at index 1:\n";
    list.display(true);
    
    list.reverse();
    std::cout << "\nAfter reversing:\n";
    list.display(true);
    
    list.sort();
    std::cout << "\nAfter sorting:\n";
    list.display(true);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void testCircularLinkedList() {
    std::cout << "\n========== TESTING CIRCULAR LINKED LIST ==========\n";
    
    CircularLinkedList<int> list;
    
    list.addLast(100);
    list.addLast(200);
    list.addLast(300);
    list.addFirst(50);
    
    std::cout << "\nAfter adding elements (50, 100, 200, 300):\n";
    list.display(true);
    std::cout << "Size: " << list.size() << std::endl;
    
    std::cout << "\nElement at index 2: " << list[2] << std::endl;
    std::cout << "Front: " << list.front() << ", Back: " << list.back() << std::endl;
    
    list.remove(200);
    std::cout << "\nAfter removing 200:\n";
    list.display(true);
    
    CircularLinkedList<int> list2;
    list2.addLast(400);
    list2.addLast(500);
    
    list.merge(list2);
    std::cout << "\nAfter merging with another list:\n";
    list.display(true);
    
    list.sort(false);
    std::cout << "\nAfter sorting (descending):\n";
    list.display(true);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void testCircularDoublyLinkedList() {
    std::cout << "\n========== TESTING CIRCULAR DOUBLY LINKED LIST ==========\n";
    
    CircularDoublyLinkedList<double> list;
    
    list.addLast(1.5);
    list.addLast(2.5);
    list.addLast(3.5);
    list.addFirst(0.5);
    
    std::cout << "\nAfter adding elements (0.5, 1.5, 2.5, 3.5):\n";
    list.display(true);
    std::cout << "Size: " << list.size() << std::endl;
    
    std::cout << "\nFront: " << list.front() << ", Back: " << list.back() << std::endl;
    
    list.removeLast();
    std::cout << "\nAfter removing last:\n";
    list.display(true);
    
    list.reverse();
    std::cout << "\nAfter reversing:\n";
    list.display(true);
    
    std::cout << "\nContains 2.5: " << (list.contains(2.5) ? "Yes" : "No") << std::endl;
    std::cout << "Index of 2.5: " << list.indexOf(2.5) << std::endl;
    
    list.clear();
    std::cout << "\nAfter clearing - isEmpty: " << (list.isEmpty() ? "Yes" : "No") << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "===============================================\n";
    std::cout << "   COMPREHENSIVE LINKED LIST IMPLEMENTATION\n";
    std::cout << "===============================================\n";
    
    try {
        testSinglyLinkedList();
        testDoublyLinkedList();
        testCircularLinkedList();
        testCircularDoublyLinkedList();
        
        std::cout << "\n===============================================\n";
        std::cout << "         ALL TESTS COMPLETED SUCCESSFULLY\n";
        std::cout << "===============================================\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
