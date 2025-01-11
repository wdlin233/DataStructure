struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

// hw6-1
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

// Or you can use
void Exchange(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    TreeNode* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    Exchange(root->left);
    Exchange(root->right);
}

// bp 树2024-(3)
