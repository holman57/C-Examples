/**
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *swapPairs(struct ListNode *head) {
    struct ListNode *ptr1;
    struct ListNode *ptr2;
    struct ListNode *ptr3;
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;
    ptr1 = head;
    head = head->next;
    ptr2 = head->next;
    head->next = ptr1;
    ptr1->next = ptr2;
    while ((ptr2 != NULL) && (ptr2->next != NULL)) {
        ptr1->next = ptr2->next;
        ptr2->next = ptr2->next->next;
        ptr1->next->next = ptr2;
        ptr1 = ptr2;
        ptr2 = ptr2->next;
    }

    return head;
}