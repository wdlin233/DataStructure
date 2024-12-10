#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

int N;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {};
};

char type_dec(const std::vector<int> str) {
    // char type = 'U';
    // for (int i = 0; i < str.size(); i++) {
    //     if (str[i] == 1 && (type == 'I' || type == 'U')) type = 'I';
    //     else if (str[i] == 0 && (type == 'B' || type == 'U')) type = 'B';
    //     else if (type == 'I' || type == 'B') type = 'F'; 
    // }
    // return type;
    bool has_zero = false;
    bool has_one = false;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 0) {
            has_zero = true;
        } else if (str[i] == 1) {
            has_one = true;
        }
    }

    if (has_zero && !has_one) {
        return 'B';  
    } else if (!has_zero && has_one) {
        return 'I';  
    } else if (has_zero && has_one) {
        return 'F'; 
    }

    return 'U';
}

TreeNode* build_tree(std::vector<int>& str, TreeNode* root) {
    char val_tmp = type_dec(str);
    //root->val = val_tmp;
    if(!root) root = new TreeNode(val_tmp);
    else root->val = val_tmp;

    std::vector<int> str_left;
    std::vector<int> str_right;
    if (str.size() > 1) { // slice
        std::size_t mid = str.size() / 2;
        str_left = std::vector<int>(str.begin(), str.begin() + mid);
        str_right = std::vector<int>(str.begin() + mid, str.end());
        root->left = build_tree(str_left, root->left);
        root->right = build_tree(str_right, root->right);
    }
    return root;
}

void traverse_back(TreeNode* root) {
    if (root->left != nullptr) traverse_back(root->left);
    if (root->right != nullptr) traverse_back(root->right);
    std::cout << root->val; 
}

int main(void) {
    std::cin >> N;
    std::cin.ignore(); //否则缓冲区会遇到一个换行符
    std::vector<int> str;

    //std::cin >> str;
    std::string input;
    std::cin >> input;
    for (char ch : input) {
        if (ch == '0') {
            str.push_back(0);
        } else if (ch == '1') {
            str.push_back(1);
        } else {
            std::cerr << "Invalid input! Only binary digits (0 or 1) are allowed." << std::endl;
            return 1;  
        }
    }
    

    TreeNode* root = new TreeNode('U');
    root = build_tree(str, root);
    traverse_back(root);
    return 0;
}