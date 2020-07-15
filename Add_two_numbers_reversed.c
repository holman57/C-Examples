/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int carry = 0;
    struct ListNode* res = (struct ListNode*)malloc(sizeof(struct ListNode));
    res -> next = NULL;
    struct ListNode* head = res;
    int flag = 0;
    while(l1 && l2 ) {
        
       res -> val  = ((l1 -> val) + (l2 -> val) + carry) % 10;
        
        if(l1 -> val + l2 -> val + carry > 9) {
            carry = 1;
        }
        else {
            carry = 0;
        }
        
        l1 = l1 -> next;
        l2 = l2 -> next;
        if(l1 && l2) {
            res -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
            res -> next -> next = NULL;
            res = res -> next;
        }
    }
    
   
    
    if(!l1 && l2) {
        while(l2) {
            res -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
            res = res -> next;
            res -> next = NULL;
            res -> val = (l2 -> val + carry) % 10;
            carry = (l2 -> val + carry) / 10;
            l2 = l2 -> next;
        }
        if(carry == 1) {
             res -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
             res = res -> next;
             res -> val = 1;
             res -> next = NULL;
        }
        flag = 1;
    }
    
    else if(!l2 && l1) {
         while(l1) {
             res -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
             res = res -> next;
             res -> next = NULL;
             res -> val = (l1 -> val + carry) % 10;
             carry = (l1 -> val + carry) / 10;
             l1 = l1 -> next;
        }
        if(carry == 1) {
             res -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
             res = res -> next;
             res -> val = 1;
             res -> next = NULL;
        }
        flag = 1;
        
    }
    
     if(carry == 1 && flag == 0) {
             res -> next = (struct ListNode*)malloc(sizeof(struct ListNode));
             res = res -> next;
             res -> val = 1;
             res -> next = NULL;
        }
    return head;
}