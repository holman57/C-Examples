/*
 *
 * Given a linked list, remove the n-th node from the end of list and return its head.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int list_len(struct ListNode *head) {
    struct ListNode *t = head;
    int i = 0;
    while (t != NULL) {
        t = t->next;
        i++;
    }
    return i;
}

struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
    struct ListNode *t = head;
    struct ListNode *ant_t = head;
    int len = list_len(head);
    if ((len - n) == 0) {
        head = head->next;
        free(t);
        return head;
    }
    len = len - n;
    if (n == 0) return head;

    while (len > 0) {
        ant_t = t;
        t = t->next;
        len--;
    }

    ant_t->next = t->next;
    free(t);
    return head;
}