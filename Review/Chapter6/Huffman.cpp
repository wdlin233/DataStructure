typedef struct {
    int weight;
    char data;
    int parent, lchild, rchild;
} HuffmanNode, *HuffmanTree;

void CreateHuffmanTree(HuffmanTree &HT, int *w, char* data, arint n) {
    if (n <= 1) return; 
    int m = 2 * n - 1; //n为叶子节点数，m为总节点数
    HT = new HuffmanNode[m + 1];
    for (int i = 1; i <= n; i++) { // initialize
        HT[i].weight = w[i - 1];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].data = data[i - 1];
    }
    for (int i = n + 1; i <= m; i++) {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].data = '#';
    }
    for (int i = n + 1; i <= m; i++) { //遍历所有非叶子节点
        int s1 = 0, s2 = 0;
        for (int j = 1; j < i; j++) { //找到两个最小的节点，权重最小且未被使用
            if (HT[j].parent != 0) continue;
            else if (s1 == 0) s1 = j; 
            else if (s2 == 0) s2 = j;
            else {
                if (HT[j].weight < HT[s1].weight) { //s1是最小权重节点
                    s2 = s1;
                    s1 = j;
                } else if (HT[j].weight < HT[s2].weight) { //s2是次小权重节点
                    s2 = j;
                }
            }
        }
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[s1].parent = i;
        HT[s2].parent = i;
    }
}

#include <iostream>
#include <string>

typedef struct {
    char data;       
    std::string code; 
} HuffmanCode;

void GenerateHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n) {
    std::string code;
    
    // 从叶子节点向上遍历到根节点，生成编码
    for (int i = 1; i <= n; i++) {
        //int start = n - 1; 
        int c = i;         
        int f = HT[i].parent; 
        
        // 从叶子节点向上遍历到根节点
        while (f != 0) {
            if (HT[f].lchild == c) {
                code = '0' + code; // 左子树路径标记为0
            } else {
                code = '1' + code; // 右子树路径标记为1
            }
            c = f;
            f = HT[f].parent;
        }
        
        //HC[i].data = HT[i].data;
        HC[i].code = code;
        code.clear(); 
    }
}
/*
Huffman Code Table:
Character: a, Code: 1100
Character: b, Code: 1101
Character: c, Code: 100
Character: d, Code: 101
Character: e, Code: 111
Character: f, Code: 0
*/
void PrintHuffmanCode(HuffmanCode *HC, int n) {
    std::cout << "Huffman Code Table:" << std::endl;
    for (int i = 1; i <= n; i++) {
        std::cout << "Character: " << HC[i].data << ", Code: " << HC[i].code << std::endl;
    }
}

int main() {
    int w[] = {5, 9, 12, 13, 16, 45};
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int n = sizeof(w) / sizeof(w[0]);
    
    HuffmanTree HT;
    CreateHuffmanTree(HT, w, data, n);
    
    HuffmanCode *HC = new HuffmanCode[n + 1];
    GenerateHuffmanCode(HT, HC, n);
    PrintHuffmanCode(HC, n);
    
    delete[] HT;
    delete[] HC;
    return 0;
}