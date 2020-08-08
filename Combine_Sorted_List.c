/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode NODE;
struct ListNode *PNODE;

struct ListNode *mergeTwoLists(struct ListNode *l1, struct ListNode *l2) {
    int i;

    struct ListNode *pHead = (struct ListNode *) malloc(sizeof(NODE));
    struct ListNode *p = (struct ListNode *) malloc(sizeof(NODE));

    if (!l1 && !l2) return 0;
    else if (!l1) return l2;
    else if (!l2) return l1;

    for (i = 0; l1; i++) {
        if (!i) {
            if (l1->val <= l2->val) {
                p->val = l1->val;
                p->next = NULL;
                l1 = l1->next;
            } else {
                p->val = l2->val;
                p->next = NULL;
                l2 = l2->next;
            }
            pHead = p;
        } else if (l2) {
            if (l1->val <= l2->val) {
                p->next = l1;
                p = p->next;
                p->val = l1->val;
                l1 = l1->next;
            } else {
                p->next = l2;
                p = p->next;
                p->val = l2->val;
                l2 = l2->next;
            }
        } else {
            p->next = l1;
            p = p->next;
            p->val = l1->val;
            l1 = l1->next;
        }
    }

    for (i = 0; l2; i++) {
        p->next = l2;
        p = p->next;
        p->val = l2->val;
        l2 = l2->next;
    }

    return pHead;
}