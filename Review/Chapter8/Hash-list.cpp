#include <iostream>
#include <vector>
#include <list>

// 链地址法
class HashTable {
private:
    int size;
    std::vector<std::list<int>> table; // 使用链表存储每个槽位的键值

public:
    HashTable(int size) : size(size) {
        table.resize(size); // 初始化每个槽位的链表
    }

    // 哈希函数
    int hashFunction(int key) {
        return key % size;
    }

    // 插入键值
    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key); // 将键值添加到对应槽位的链表中
    }

    // 查找键值
    bool search(int key) {
        int index = hashFunction(key);
        for (int value : table[index]) {
            if (value == key) {
                return true; // 找到键值
            }
        }
        return false; // 未找到键值
    }

    // 删除键值
    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key); // 从链表中删除键值
    }

    // 显示哈希表
    void display() {
        for (int i = 0; i < size; i++) {
            std::cout << "Index " << i << ": ";
            for (int value : table[i]) {
                std::cout << value << " -> ";
            }
            std::cout << "NULL" << std::endl;
        }
    }
};

int main() {
    HashTable ht(10);

    // 插入键值
    ht.insert(5);
    ht.insert(15);
    ht.insert(25);
    ht.insert(7);
    ht.insert(17);
    ht.insert(27);

    // 显示哈希表
    ht.display();

    // 查找键值
    std::cout << "Search 15: " << (ht.search(15) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 20: " << (ht.search(20) ? "Found" : "Not Found") << std::endl;

    // 删除键值
    ht.remove(15);
    std::cout << "After removing 15:" << std::endl;
    ht.display();

    return 0;
}