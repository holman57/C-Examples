#include <stdio.h>
#include <stdlib.h>

struct ListNode {
     int val;
     struct ListNode *next;
};
 
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* head = malloc(sizeof(struct ListNode));
    struct ListNode* tail = head;
    head->val = 0;
    head->next = tail;
    int carry = 0;
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int digit1 = (l1 != NULL) ? l1->val : 0;
        int digit2 = (l2 != NULL) ? l2->val : 0;
        int sum = digit1 + digit2 + carry;
        int resultDigit = sum % 10;
        carry = (int)(sum / 10);
        struct ListNode* node = malloc(sizeof(struct ListNode));
        node->val = resultDigit;
        if (l1 != NULL) l1 = l1->next; else NULL;
        if (l2 != NULL) l2 = l2->next; else NULL;
        tail->next = node;
        tail = tail->next;
    }
    tail->next = NULL;
    return head->next;
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