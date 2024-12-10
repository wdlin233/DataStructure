#include <iostream>
#include <algorithm>
#include <vector>

struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};
char pre_str[51] = {0};
char in_str[51] = {0};

TreeNode* buildTree(const char* preorder, const char* inorder, int inorder_start, int inorder_end, int& preorder_index) {
    if (inorder_start > inorder_end) {
        return nullptr;
    }
    
    char root_val = preorder[preorder_index++];
    TreeNode* root = new TreeNode(root_val);
    
    if (inorder_start == inorder_end) {
        return root;
    }
    
    int inorder_index = 0;
    for (int i = inorder_start; i <= inorder_end; i++) {
        if (inorder[i] == root_val)
            inorder_index = i;
    }
    
    root->left = buildTree(preorder, inorder, inorder_start, inorder_index - 1, preorder_index);
    root->right = buildTree(preorder, inorder, inorder_index + 1, inorder_end, preorder_index);
    
    return root;
}

TreeNode* buildTree(const char* preorder, const char* inorder, int length) {
    int preorder_index = 0;
    return buildTree(preorder, inorder, 0, length - 1, preorder_index);
}

void post_order_println(TreeNode* root) {
    if (root != nullptr) {
        post_order_println(root->left);
        post_order_println(root->right);
        std::cout << root->val;
    }
}


// That's WRONG.
// void post_order_println_mirror(TreeNode* root) {
//     if (root != nullptr) {
//         post_order_println(root->right);
//         post_order_println(root->left);
//         std::cout << root->val;
//     }
// }

TreeNode* mirrorTree(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    
    TreeNode* left = mirrorTree(root->left);
    TreeNode* right = mirrorTree(root->right);
    
    root->left = right;
    root->right = left;
    
    return root;
}

int main(void) {
    std::cin >> pre_str;
    std::cin >> in_str;
    int length = 0;
    while (pre_str[length] != '\0') {
        length++;
    }
    TreeNode* root = buildTree(pre_str, in_str, length);
    post_order_println(root);
    std::cout << std::endl;
    root = mirrorTree(root);
    // post_order_println_mirror(root);
    post_order_println(root);
    return 0;
}