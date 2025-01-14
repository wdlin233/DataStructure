#include <iostream>
#include <vector>

using namespace std;

// 多阶平衡搜素树，对m阶B树
// 最多：m个分支，m-1个元素
// 最少：根节点2个分支，一个元素；其他节点m/2（上取整）个分支，m/2（上取整）-1个元素
class BTreeNode {
public:
    vector<int> keys;          // 存储键值
    vector<BTreeNode*> children; // 存储子节点指针
    bool isLeaf;               // 是否为叶子节点
    int t;                     // 最小度数（决定节点的最小和最大键数）

    BTreeNode(int _t, bool _isLeaf) : t(_t), isLeaf(_isLeaf) {
        keys.reserve(2 * t - 1);
        children.reserve(2 * t);
    }

    // 查找键值是否在节点中
    int findKey(int k) {
        int idx = 0;
        while (idx < keys.size() && keys[idx] < k)
            ++idx;
        return idx;
    }

    // 插入键值到非满节点
    void insertNonFull(int k) {
        int i = keys.size() - 1;

        if (isLeaf) {
            keys.push_back(0);
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
        } else {
            while (i >= 0 && keys[i] > k)
                i--;

            if (children[i + 1]->keys.size() == 2 * t - 1) {
                splitChild(i + 1, children[i + 1]);

                if (keys[i + 1] < k)
                    i++;
            }
            children[i + 1]->insertNonFull(k);
        }
    }

    // 分裂子节点
    void splitChild(int i, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
        z->keys.resize(t - 1);

        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];

        if (!y->isLeaf) {
            z->children.resize(t);
            for (int j = 0; j < t; j++)
                z->children[j] = y->children[j + t];
        }

        y->keys.resize(t - 1);
        children.insert(children.begin() + i + 1, z);
        keys.insert(keys.begin() + i, y->keys[t - 1]);
    }

    // 删除键值
    void remove(int k) {
        int idx = findKey(k);

        if (idx < keys.size() && keys[idx] == k) {
            if (isLeaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        } else {
            if (isLeaf) {
                cout << "Key " << k << " does not exist in the tree\n";
                return;
            }

            bool flag = (idx == keys.size());

            if (children[idx]->keys.size() < t)
                fill(idx);

            if (flag && idx > keys.size())
                children[idx - 1]->remove(k);
            else
                children[idx]->remove(k);
        }
    }

    // 从叶子节点删除键值
    void removeFromLeaf(int idx) {
        keys.erase(keys.begin() + idx);
    }

    // 从非叶子节点删除键值
    void removeFromNonLeaf(int idx) {
        int k = keys[idx];

        if (children[idx]->keys.size() >= t) {
            int pred = getPred(idx);
            keys[idx] = pred;
            children[idx]->remove(pred);
        } else if (children[idx + 1]->keys.size() >= t) {
            int succ = getSucc(idx);
            keys[idx] = succ;
            children[idx + 1]->remove(succ);
        } else {
            merge(idx);
            children[idx]->remove(k);
        }
    }

    // 获取前驱键值
    int getPred(int idx) {
        BTreeNode* cur = children[idx];
        while (!cur->isLeaf)
            cur = cur->children[cur->keys.size()];
        return cur->keys[cur->keys.size() - 1];
    }

    // 获取后继键值
    int getSucc(int idx) {
        BTreeNode* cur = children[idx + 1];
        while (!cur->isLeaf)
            cur = cur->children[0];
        return cur->keys[0];
    }

    // 填充子节点
    void fill(int idx) {
        if (idx != 0 && children[idx - 1]->keys.size() >= t)
            borrowFromPrev(idx);
        else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
            borrowFromNext(idx);
        else {
            if (idx != keys.size())
                merge(idx);
            else
                merge(idx - 1);
        }
    }

    // 从前一个子节点借键值
    void borrowFromPrev(int idx) {
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx - 1];

        child->keys.insert(child->keys.begin(), keys[idx - 1]);

        if (!child->isLeaf)
            child->children.insert(child->children.begin(), sibling->children[sibling->keys.size()]);

        keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];
        sibling->keys.pop_back();
        if (!sibling->isLeaf)
            sibling->children.pop_back();
    }

    // 从后一个子节点借键值
    void borrowFromNext(int idx) {
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx + 1];

        child->keys.push_back(keys[idx]);

        if (!child->isLeaf)
            child->children.push_back(sibling->children[0]);

        keys[idx] = sibling->keys[0];
        sibling->keys.erase(sibling->keys.begin());
        if (!sibling->isLeaf)
            sibling->children.erase(sibling->children.begin());
    }

    // 合并子节点
    void merge(int idx) {
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx + 1];

        child->keys.push_back(keys[idx]);

        for (int i = 0; i < sibling->keys.size(); i++)
            child->keys.push_back(sibling->keys[i]);

        if (!child->isLeaf) {
            for (int i = 0; i <= sibling->keys.size(); i++)
                child->children.push_back(sibling->children[i]);
        }

        keys.erase(keys.begin() + idx);
        children.erase(children.begin() + idx + 1);

        delete sibling;
    }

    // 查找键值
    BTreeNode* search(int k) {
        int i = 0;
        while (i < keys.size() && k > keys[i])
            i++;

        if (i < keys.size() && keys[i] == k)
            return this;

        if (isLeaf)
            return nullptr;

        return children[i]->search(k);
    }

    // 打印B树
    void traverse() {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!isLeaf)
                children[i]->traverse();
            cout << " " << keys[i];
        }

        if (!isLeaf)
            children[i]->traverse();
    }
};

// B树类
class BTree {
public:
    BTreeNode* root;
    int t;

    BTree(int _t) : t(_t), root(nullptr) {}

    // 插入键值
    void insert(int k) {
        if (root == nullptr) {
            root = new BTreeNode(t, true);
            root->keys.push_back(k);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode* s = new BTreeNode(t, false);
                s->children.push_back(root);
                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->children[i]->insertNonFull(k);

                root = s;
            } else {
                root->insertNonFull(k);
            }
        }
    }

    // 删除键值
    void remove(int k) {
        if (!root) {
            cout << "The tree is empty\n";
            return;
        }

        root->remove(k);

        if (root->keys.size() == 0) {
            BTreeNode* tmp = root;
            if (root->isLeaf)
                root = nullptr;
            else
                root = root->children[0];
            delete tmp;
        }
    }

    // 查找键值
    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // 打印B树
    void traverse() {
        if (root != nullptr)
            root->traverse();
    }
};

// 测试代码
int main() {
    BTree t(3); // 最小度数 t=3

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed tree is ";
    t.traverse();
    cout << endl;

    t.remove(6);
    cout << "Traversal after deletion of 6\n";
    t.traverse();
    cout << endl;

    t.remove(13);
    cout << "Traversal after deletion of 13\n";
    t.traverse();
    cout << endl;

    t.remove(7);
    cout << "Traversal after deletion of 7\n";
    t.traverse();
    cout << endl;

    t.remove(4);
    cout << "Traversal after deletion of 4\n";
    t.traverse();
    cout << endl;

    t.remove(20);
    cout << "Traversal after deletion of 20\n";
    t.traverse();
    cout << endl;

    return 0;
}
