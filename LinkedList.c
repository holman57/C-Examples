#import <stdio.h>
#import <stdlib.h>

struct ListNode {
     int val;
     struct ListNode *next;
 };
 
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* r = malloc(sizeof(struct ListNode));
    r->val = 0;
    r->next = NULL;
    struct ListNone* init = r;
    while(l1 || l2) {
        if(l1) {
            r->val += l1->val;
            l1 = l1->next;
        }
        if(l2) {
            r->val += l2->val;
            l2 = l2->next;
        }
        if((r->val > 9) || l1 || l2) {
            struct ListNode* next = malloc(sizeof(struct ListNode));
            next->val = 0;
            next->next = NULL;
            if(r->val > 9) {
                r->val = r->val - 10;
                next->val += 1;
            }
            r->next = next;
            r = next;
        }
    }
    return init;
}

int main() {
    struct ListNode* l1 = malloc(sizeof(struct ListNode));
    struct ListNode* i2 = malloc(sizeof(struct ListNode));
    struct ListNode* i3 = malloc(sizeof(struct ListNode));
    l1->val = 2;
    i2->val = 4;
    l1->next = i2;
    i3->val = 3;
    i2->next = i3;
    i3->next = NULL;

    struct ListNode* l2 = malloc(sizeof(struct ListNode));
    struct ListNode* i4 = malloc(sizeof(struct ListNode));
    struct ListNode* i5 = malloc(sizeof(struct ListNode));
    l2->val = 5;
    i4->val = 6;
    l2->next = i4;
    i5->val = 4;
    i4->next = i5;
    i5->next = NULL;
    
    struct ListNode* l3 = addTwoNumbers(l1, l2);
    while (l3 != NULL) {
        printf("%d\n", l3->val);
        l3 = l3->next;
    }
    
    return 0;
}
