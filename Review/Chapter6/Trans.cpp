/*
1.由先序和中序可以唯一确定一棵二叉树
2.由后序和中序可以唯一确定一棵二叉树
3.由先序和后序**不能**唯一确定一棵二叉树
*/

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//中序和先序确定二叉树
BiTree PreInCreate(
    int pre[],  // 前序遍历序列数组
    int in[],   // 中序遍历序列数组
    int pre_start,     // pre-start: 当前前序序列的起始位置
    int pre_end,     // pre-end: 当前前序序列的结束位置
    int in_start,     // in-start: 当前中序序列的起始位置
    int in_end      // in-end: 当前中序序列的结束位置
) {
    if (pre_start > pre_end) return NULL;
    
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = pre[pre_start];
    
    // 在中序序列中找到根节点位置
    int pos;
    for (pos = in_start; pos <= in_end; pos++) {
        if (in[pos] == pre[pre_start]) break;
    }
    
    int llen = pos - in_start;  // 左子树长度
    
    // 递归构建左右子树
    root->lchild = PreInCreate(pre, in, pre_start+1, pre_start+llen, in_start, pos-1);
    root->rchild = PreInCreate(pre, in, pre_start+llen+1, pre_end, pos+1, in_end);
    
    return root;
}

// 主函数调用入口
BiTree CreateByPreIn(int pre[], int in[], int n) {
    if (n == 0) return NULL;
    return PreInCreate(pre, in, 0, n-1, 0, n-1);
}

    

