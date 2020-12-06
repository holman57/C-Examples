// unique triplets in the array which gives the sum of zero.

int cmp(const void *a, const void b)
{
    return (int) a - (int) b;
}

typedef struct Node
{
    int array[3];
    struct Node next;
} Node;

Node *Create(int a, int b, int c)
{
    Node node = (Node) malloc(sizeof(Node));
    node->array[0] = a;
    node->array[1] = b;
    node->array[2] = c;
    node->next = NULL;
    return node;
}

int threeSum(int ss, int n, int returnSize, int returnColumnSizes)
{
    qsort(ss, n, sizeof(int), cmp);
    *returnSize = 0;
    int p;
    Node head, end;
    head = (Node) malloc(sizeof(Node));
    head->next = NULL;
    end = head;
    if (n == 3)
    {
        if (ss[0] + ss[1] + ss[2] == 0)
        {
            returnSize = 1;
            p = (int) malloc(sizeof(int));
            p[0] = (int) malloc(12);
            returnColumnSizes = (int) malloc(sizeof(int));
            (*returnColumnSizes)[0] = 3;
            p[0][0] = ss[0];
            p[0][1] = ss[1];
            p[0][2] = ss[2];
        }
    }
    if (n > 3)
    {
        int count = 1;
        int signal = 1;
        int l = 0, x = 1, r = n - 1;
        int i, k, j;
        int count_0 = 0;
        if (ss[0] == 0)count_0++;
        for (i = 1; i < n; i++)
        {
            if (ss[i] == 0)
            {
                if (count_0 >= 3)continue;
                count_0++;
                count++;
            } else if (ss[i] == ss[i - 1] && signal)
            {
                count++;
                signal = 0;
            } else if (ss[i] != ss[i - 1])
            {
                count++;
                signal = 1;
            }
        }
        int s[count];
        count_0 = 0;
        if (ss[0] == 0)count_0++;
        s[0] = ss[0];
        signal = 1;
        for (i = 1, j = 1; i < n; i++)
        {
            if (ss[i] == 0)
            {
                // printf("%d\n", count_0);
                if (count_0 >= 3)continue;
                count_0++;
                // printf("%d\n", j);
                s[j++] = ss[i];
            } else if (ss[i] == ss[i - 1] && signal)
            {
                s[j++] = ss[i];
                signal = 0;
            } else if (ss[i] != ss[i - 1])
            {
                s[j++] = ss[i];
                signal = 1;

            }
        }
        //keep 2 of duplicate numbers and 3 of zero
        n = count;
        int record_maxr = n - 1;
        for (l = 0; l < n - 1; l++)
        {
            if (s[l] > 0)break;
            x = l + 1;
            signal = 1;
            for (r = record_maxr; r > l; r--)
            {

                for (; x < r; x++)
                {
                    if (s[l] + s[r] + s[x] > 0)
                    {
                        break;
                    }
                    if (signal)record_maxr = r;
                    signal = 0;
                    if (s[l] + s[r] + s[x] == 0)
                    {
                        Node *node = Create(s[l], s[x], s[r]);
                        end->next = node;
                        end = node;
                        (*returnSize)++;
                        break;
                    }
                }
                if (r > 1)
                {
                    if (s[r] == s[r - 1])
                    {
                        r--;
                    }
                }
            }
            if (l < n - 1)
            {
                if (s[l] == s[l + 1])
                {
                    l++;
                }
            }
        }
        p = (int **) malloc((*returnSize) * sizeof(int *));
        *returnColumnSizes = (int *) malloc((*returnSize) * sizeof(int));
        Node *t = head;
        Node *t1 = head;
        for (i = 0; t->next != NULL;)
        {
            t = t->next;
            p[i] = t->array;
            (*returnColumnSizes)[i++] = 3;
        }
    }

    return p;
}