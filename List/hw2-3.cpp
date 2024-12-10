#include <iostream>
#include <algorithm>
#include <list>

// std::list<int> L;
int N = 0, Target = 0; 

struct ListNode{
	int val;
	ListNode *next;
    ListNode *prior;
	ListNode() : val(0),next(NULL){}
	ListNode(int x) : val(x), next(NULL){}
	ListNode(int x, ListNode *next) : val(x), next(next){}
    ListNode(int x, ListNode *next, ListNode *prior) : val(x), next(next), prior(prior){}
}; 
ListNode *L = new ListNode();
ListNode *Head = L;

int main(void){
    std::cin >> N;
    int first_val = 0;
    std::cin >> first_val;
    L->val = first_val;
    for (int i = 0, tmp = 0; i < N - 1; i++) {
        std::cin >> tmp;
        ListNode *node = new ListNode(tmp);
        node->prior = L;
        L->next = node;
        L = L->next;
        // L.push_back(tmp);
        if (i == N - 2){
            L->next = Head;
            Head->prior = L;
        }  
    }

    std::cin >> Target;
    L = Head;
    ListNode *from;
    for (int i = 0; i < N; i++) {
        if (L->val == Target) from = L;  
        else L = L->next;
    }
    for (int i = 0; i < N; i++) {
        std::cout << from->val << ' ';
        from = from->prior;
    }
    
    return 0;
}