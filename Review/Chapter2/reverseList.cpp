struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
  
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
            ListNode* prev = nullptr;
            ListNode* curr = head;
            ListNode* next_node = nullptr; 
            while(curr != nullptr) {
                next_node = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next_node;
            }
            return prev;
    }
    
    ListNode* reverseList2(ListNode* head) {
            //if (head->next == nullptr || head == nullptr) return head;
            // It CANT be. nullptr->next
            if (head == nullptr || head->next == nullptr) return head;
            // head==null for tail
            // head->next==null for head
            ListNode* next_node = reverseList(head->next);
            //next_node->next = head;
            //It CANT be.
            // [1, 2, 3, 4,  5] then Node(5)->Node(1)
            head->next->next=head;
            head->next=nullptr;
            return next_node;
    }
};