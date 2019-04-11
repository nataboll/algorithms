#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    
    ListNode *ans = new ListNode(0);
    
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *tmp = ans;
        int in_mind = 0;
        tmp->val = (l1->val + l2->val)%10;
        in_mind = (l1->val + l2->val)/10;
        l1 = l1->next;
        l2 = l2->next;
        while (l1 && l2) {
            tmp->next = new ListNode(0);
            tmp = tmp->next;
            
            tmp->val = (l1->val + l2->val + in_mind) % 10;
            in_mind = (l1->val + l2->val + in_mind) / 10;
            
            l1 = l1->next;
            l2 = l2->next;
        }
        
        while (l1) {
            tmp->next = new ListNode(0);
            tmp = tmp->next;
            tmp->val = (l1->val + in_mind) % 10;
            in_mind = (l1->val + in_mind) / 10;
            l1 = l1->next;
        }
        
        while (l2) {
            tmp->next = new ListNode(0);
            tmp = tmp->next;
            tmp->val = (l2->val + in_mind) % 10;
            in_mind = (l2->val + in_mind) / 10;
            l2 = l2->next;
        }
        
        if (in_mind) 
            tmp->next = new ListNode(in_mind);
        
        return ans;
    }
};

int main() {
    ListNode *root1 = new ListNode(2);
    ListNode *root2 = new ListNode(5);
    ListNode *r12 = new ListNode(4);
    root1->next = r12;
    ListNode *r13 = new ListNode(3);
    r12->next = r13;
    ListNode *r22 = new ListNode(6);
    root2->next = r22;
    ListNode *r23 = new ListNode(4);
    r22->next = r23;
    Solution sol;
    ListNode *root = sol.addTwoNumbers(root1, root2);
    while (root) {
        std::cout << root->val << " ";
        root = root->next;
    }
    std::cout << std::endl;
    return 0;
}
