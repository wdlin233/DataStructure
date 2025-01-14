/*
构造方法
1.直接地址法
    H(key) = a * key + b
2.数字分析法
    取key中随机性较好的几位
3.平方取中法
    key^2的中间几位
4.叠加法 
    key分割为位数相同的几部分，相加作H(key)哈希地址
5.保留余数法
    H(key) = key % p
6.随机函数法
    H(key) = C * random(key)

冲突解决方法
1.开放定址法
    H(key, i) = (H(key) + d(i)) % m, m为表长，d(i)为增量序列  
    1.1 线性探测法
        H(key, i) = (H(key) + i) % m
    1.2 二次探测法
        H(key, i) = (H(key) + c1 * i + c2 * i^2) % m
    1.3 双散列法
        H(key, i) = (H1(key) + i * H2(key)) % m
2.链地址法
*/
#include <iostream>
#include <vector>

class HashTable {
private:
    int size;
    std::vector<int> table;
    int c1, c2; // Constants for quadratic probing

public:
    HashTable(int size, int c1 = 1, int c2 = 1) : size(size), c1(c1), c2(c2) {
        table.resize(size, -1); // Initialize all slots to -1 (indicating empty)
    }

    // Hash function using linear probing
    int linearProbing(int key, int i) {
        return (key % size + i) % size;
    }

    // Hash function using quadratic probing
    int quadraticProbing(int key, int i) {
        return (key % size + c1 * i + c2 * i * i) % size;
    }
    /*
    线性探测的优缺点：
    优点：
    1. 实现简单，易于理解和实现。
    2. 在表未满时，总能找到一个空闲位置插入元素。
    缺点：
    1. 容易产生“聚集”现象，即连续的冲突导致查找效率下降。
    2. 当表接近满时，插入和查找的时间复杂度会显著增加。

    二次探测的优缺点：
    优点：
    1. 减少了“聚集”现象，冲突分布更加均匀。
    2. 在表未满时，通常能更快地找到空闲位置。
    缺点：
    1. 实现相对复杂，需要选择合适的常数c1和c2。
    2. 在某些情况下，可能无法找到空闲位置，即使表未满。
    */

    // Insert using linear probing
    void insertLinear(int key) {
        int i = 0;
        int index = linearProbing(key, i);
        while (table[index] != -1) {
            i++;
            index = linearProbing(key, i);
        }
        table[index] = key;
    }

    // Insert using quadratic probing
    void insertQuadratic(int key) {
        int i = 0;
        int index = quadraticProbing(key, i);
        while (table[index] != -1) {
            i++;
            index = quadraticProbing(key, i);
        }
        table[index] = key;
    }

    // Search using linear probing
    bool searchLinear(int key) {
        int i = 0;
        int index = linearProbing(key, i);
        while (table[index] != -1) {
            if (table[index] == key) {
                return true;
            }
            i++;
            index = linearProbing(key, i);
        }
        return false;
    }

    // Search using quadratic probing
    bool searchQuadratic(int key) {
        int i = 0;
        int index = quadraticProbing(key, i);
        while (table[index] != -1) {
            if (table[index] == key) {
                return true;
            }
            i++;
            index = quadraticProbing(key, i);
        }
        return false;
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < size; i++) {
            std::cout << "Index " << i << ": " << table[i] << std::endl;
        }
    }
};

int main() {
    HashTable ht(10);

    // Insert using linear probing
    ht.insertLinear(5);
    ht.insertLinear(15);
    ht.insertLinear(25);

    // Insert using quadratic probing
    ht.insertQuadratic(7);
    ht.insertQuadratic(17);
    ht.insertQuadratic(27);

    // Display the hash table
    ht.display();

    // Search using linear probing
    std::cout << "Search 15 (Linear): " << (ht.searchLinear(15) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 20 (Linear): " << (ht.searchLinear(20) ? "Found" : "Not Found") << std::endl;

    // Search using quadratic probing
    std::cout << "Search 17 (Quadratic): " << (ht.searchQuadratic(17) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 30 (Quadratic): " << (ht.searchQuadratic(30) ? "Found" : "Not Found") << std::endl;

    return 0;
}
