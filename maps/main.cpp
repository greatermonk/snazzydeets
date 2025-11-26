#include<iostream>
#include "maps.hpp"

int main() {
    try {
        std::cout << "========================================\n";
        std::cout << "    MAP DATA STRUCTURES DEMO\n";
        std::cout << "========================================\n";

        // ========== HASH MAP DEMO ==========
        std::cout << "\n[1] HASH MAP DEMONSTRATION\n";
        HashMap<int, std::string> hashMap;
        
        hashMap.insert(1, "Apple");
        hashMap.insert(2, "Banana");
        hashMap.insert(3, "Cherry");
        hashMap.insert(4, "Date");
        hashMap.display(true);

        std::cout << "Key 2 exists: " << (hashMap.exists(2) ? "Yes" : "No") << "\n";
        std::cout << "Value 'Cherry' exists: " << (hashMap.existsValue("Cherry") ? "Yes" : "No") << "\n";

        hashMap[5] = "Elderberry";
        std::cout << "\nAfter adding via operator[]:\n";
        hashMap.display(true);

        hashMap.erase(3);
        std::cout << "After erasing key 3:\n";
        hashMap.display(true);

        // Create from arrays
        HashMap<int, std::string> hashMap2;
        std::vector<int> keys = {10, 20, 30};
        std::vector<std::string> vals = {"Ten", "Twenty", "Thirty"};
        hashMap2.create_map_from_arrays(keys, vals);
        std::cout << "HashMap created from arrays:\n";
        hashMap2.display(true);

        // Merge maps
        auto merged = hashMap + hashMap2;
        std::cout << "Merged HashMap:\n";
        merged.display(true);

        // ========== TREE MAP DEMO ==========
        std::cout << "\n[2] TREE MAP DEMONSTRATION\n";
        TreeMap<int, std::string> treeMap;
        
        treeMap.insert(50, "Fifty");
        treeMap.insert(30, "Thirty");
        treeMap.insert(70, "Seventy");
        treeMap.insert(20, "Twenty");
        treeMap.insert(40, "Forty");
        treeMap.insert(60, "Sixty");
        treeMap.insert(80, "Eighty");
        treeMap.display(true);

        std::cout << "TreeMap is sorted by key automatically!\n";
        auto treeKeys = treeMap.keys();
        std::cout << "Keys in order: ";
        for (const auto& k : treeKeys) {
            std::cout << k << " ";
        }
        std::cout << "\n\n";

        treeMap.erase(30);
        std::cout << "After erasing key 30:\n";
        treeMap.display(true);

        // ========== LINKED LIST MAP DEMO ==========
        std::cout << "\n[3] LINKED LIST MAP DEMONSTRATION\n";
        LinkedListMap<std::string, int> listMap;
        
        listMap.insert("Alpha", 100);
        listMap.insert("Beta", 200);
        listMap.insert("Gamma", 300);
        listMap.insert("Delta", 400);
        listMap.display(true);

        std::cout << "Value at 'Beta': " << listMap.at("Beta") << "\n\n";

        listMap["Epsilon"] = 500;
        std::cout << "After adding via operator[]:\n";
        listMap.display(true);

        listMap.sort_by("key");
        std::cout << "After sorting by key:\n";
        listMap.display(true);

        // Erase multiple keys
        std::vector<std::string> keysToDelete = {"Beta", "Delta"};
        listMap.erase(keysToDelete);
        std::cout << "After erasing multiple keys:\n";
        listMap.display(true);

        // ========== ADVANCED FEATURES ==========
        std::cout << "\n[4] ADVANCED FEATURES\n";
        
        HashMap<int, int> numMap;
        numMap.insert(5, 50);
        numMap.insert(3, 30);
        numMap.insert(7, 70);
        numMap.insert(1, 10);
        
        std::cout << "Original HashMap:\n";
        numMap.display(true);
        
        numMap.sort_by("key");
        std::cout << "After sorting by key:\n";
        numMap.display(true);

        auto allPairs = numMap.pairs();
        std::cout << "All key-value pairs:\n";
        for (const auto& p : allPairs) {
            std::cout << "  " << p.first << " => " << p.second << "\n";
        }
        
        std::cout << "\nTotal size: " << numMap.size() << "\n";

        numMap.clear();
        std::cout << "\nAfter clearing:\n";
        numMap.display(true);

        std::cout << "\n========================================\n";
        std::cout << "    DEMO COMPLETED SUCCESSFULLY!\n";
        std::cout << "========================================\n";

    } catch (const MapException& e) {
        std::cerr << "Map Error: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
