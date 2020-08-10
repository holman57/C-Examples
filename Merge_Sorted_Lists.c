/*
 *  Merge k sorted linked lists and return it as one sorted list.
 * Input:
 * [
 *   1->4->5,
 *   1->3->4,
 *   2->6
 * ]
 * Output: 1->1->2->3->4->4->5->6
 * */

/* Heap implemented  here is Min Heap */
struct Heap {
    int len;   // Allocate lenth
    int heapSize;
    struct ListNode **heap;
};

/*Initialize Heap*/
void HeapInit_(struct Heap *pq, int len) {
    pq->heap = malloc(sizeof(struct ListNode *) * (len + 2));
    pq->len = len;
    pq->heapSize = 0;
    pq->heap[0] = 0;
}

void HeapDistroy(struct Heap *pq) {
    free(pq->heap);
    pq->len = 0;
    pq->heapSize = 0;
}

/*Insert an element into the heap */
void InsertMin(struct Heap *pq, struct ListNode *element) {
    pq->heapSize++;
    pq->heap[pq->heapSize] = element; /*Insert in the last place*/
    /*Adjust its position*/
    int now = pq->heapSize;
    while (now > 1 && pq->heap[now / 2]->val > element->val) {
        pq->heap[now] = pq->heap[now / 2];
        now /= 2;
    }
    pq->heap[now] = element;
}

/*Insert an element into the heap */

struct ListNode *DeleteMin(struct Heap *pq) {
    /* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased.
     Now heap[1] has to be filled. We put the last element in its place and see if it fits.
     If it does not fit, take minimum element among both its children and replaces parent with it.
     Again See if the last element fits in that place.*/
    struct ListNode *minElement, *lastElement;
    int child, now;

    if (pq->heapSize < 1) return 0;

    minElement = pq->heap[1];
    if (!minElement) return 0;
    lastElement = minElement->next;
    if (!lastElement)
        lastElement = pq->heap[pq->heapSize--];

    /* now refers to the index at which we are now */
    for (now = 1; now * 2 <= pq->heapSize; now = child) {
        /* child is the index of the element which is minimum among both the children */
        /* Indexes of children are i*2 and i*2 + 1*/
        child = now * 2;
        /*child!=pq->heapSize beacuse pq->heap[pq->heapSize+1] does not exist, which means it has only one
         child */
        if (child != pq->heapSize && pq->heap[child + 1]->val < pq->heap[child]->val) {
            child++;
        }
        /* To check if the last element fits ot not it suffices to check if the last element
         is less than the minimum element among both the children*/
        if (lastElement->val > pq->heap[child]->val) {
            pq->heap[now] = pq->heap[child];
        } else /* It fits there */
        {
            break;
        }
    }
    pq->heap[now] = lastElement;
    return minElement;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
    struct ListNode **mylist = malloc(sizeof(struct ListNode *) * listsSize);
    struct Heap pq;
    HeapInit_(&pq, listsSize);

    for (int i = 0; i < listsSize; i++) {
        if (lists[i]) {
            mylist[i] = lists[i];
            InsertMin(&pq, mylist[i]);
        }
    }

    struct ListNode *mergeKLists = 0;
    struct ListNode **p_mergeKLists = &mergeKLists;

    while (((*p_mergeKLists) = DeleteMin(&pq)))
        p_mergeKLists = &(*p_mergeKLists)->next;

    free(mylist);
    return mergeKLists;
}
