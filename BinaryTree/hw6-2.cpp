#include <iostream>

struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* root = new TreeNode(' ');

// TreeNode* find(TreeNode* root, char tagret) {
//     if (root != nullptr) {
//         if (root->val == tagret)
//             return root;
//         else {
//             find(root->left, tagret);
//             find(root->right, tagret);
//         }
//     }
//     else
//         return nullptr;
// }

TreeNode* find(TreeNode* root, char target) {
    if (root == nullptr)
        return nullptr;
    if (root->val == target)
        return root;
    TreeNode* leftResult = find(root->left, target);  // 递归查找左子树
    if (leftResult != nullptr)
        return leftResult;
    return find(root->right, target);  // 如果左子树没有找到，则查找右子树
}

// void buildTree(char F, char C, char LR) {
//     if (F == '^')
//         root->val = C;
//     else {
//         TreeNode* tmp = find(root, F);
//         if (LR == 'L') tmp->left->val = C;
//         else if (LR == 'R') tmp->right->val = C; 
//     }
// }
void buildTree(char F, char C, char LR) {
    if (F == '^')
        root->val = C;
    else {
        TreeNode* tmp = find(root, F);
        if (tmp != nullptr) {  // 确保找到了父节点
            if (LR == 'L') {
                if (tmp->left == nullptr)  // 如果左子节点不存在，先创建
                    tmp->left = new TreeNode(C);
                else
                    tmp->left->val = C;  // 如果已经存在，直接赋值
            } else if (LR == 'R') {
                if (tmp->right == nullptr)  // 如果右子节点不存在，先创建
                    tmp->right = new TreeNode(C);
                else
                    tmp->right->val = C;  // 如果已经存在，直接赋值
            }
        }
    }
}

void println_tree(TreeNode* root) {
    if (root == nullptr) return;
    std::cout << root->val;

    if (root->left != nullptr || root->right != nullptr) {
        std::cout << '(';
        if (root->left != nullptr)
            println_tree(root->left);
        // else
        //     std::cout << ' ';

        

        if (root->right != nullptr) {
            std::cout << ',';
            println_tree(root->right);
        }
        // else 
        //     std::cout << ' ';
        std::cout << ')';
    }
}

int main(void) {
    char F, C, LR;
    while(std::cin >> F >> C >> LR) {
        if (F == '^' && C == '^') break;
        else buildTree(F, C, LR);
    }
    println_tree(root);
    return 0;
}