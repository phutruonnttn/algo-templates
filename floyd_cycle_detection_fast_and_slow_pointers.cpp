/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            if (head == nullptr) {
                return head;
            }
            ListNode *slow = head;
            ListNode *fast = head;
    
            do {
                slow = slow->next;
                if (fast->next == nullptr || fast->next->next == nullptr) {
                    return nullptr;
                } else {
                    fast = fast->next->next;
                } 
            } while (slow != fast);
    
            fast = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
    
            return fast;
        }
    };