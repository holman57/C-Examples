/*
 * https://swtch.com/~rsc/regexp/nfa.c.txt
Given an input string (s) and a pattern (p), implement regular expression
matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by
repeating 'a' once, it becomes "aa".

 Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
 * */
#define CATENATE_SYMB  '\1'

char *re2post(char *re) {
    int natom = 0;
    static char buf[256];
    char *dst = buf;

    if (strlen(re) >= sizeof buf / 2)
        return NULL;

    for (; *re; re++) {
        switch (*re) {
            case '*':
                if (natom == 0)
                    return NULL;
                *dst++ = *re;
                break;
            default:
                if (natom > 1) {
                    --natom;
                    *dst++ = CATENATE_SYMB;
                }
                *dst++ = *re;
                natom++;
                break;
        }
    }
    while (--natom > 0)
        *dst++ = CATENATE_SYMB;
    *dst = 0;
    return buf;
}

/*
 * Represents an NFA state plus zero or one or two arrows exiting.
 * if c == Match, no arrows out; matching state.
 * If c == Split, unlabeled arrows to out and out1 (if != NULL).
 * If c < 256, labeled arrow with character c to out.
 */
enum {
    Match = 256, Split = 257
};

typedef struct State State;
struct State {
    int c;
    State *out;
    State *out1;
    int lastlist;
};
State matchstate = {Match};   /* matching state */
int nstate = 0;

State *_ptrstates[256];
State _states[256];
State *_states_cur_ptr;

/* Allocate and initialize State */
State *state(int c, State *out, State *out1) {
    State *s = _states_cur_ptr++;
    nstate++;
    s->c = c;
    s->out = out;
    s->out1 = out1;
    s->lastlist = 0;
    return s;
}

/*
 * A partially build NFA without the matching state filled in.
 * Frag.start points at the start state.
 * Frag.out is a list of places that need to be set to the
 * next state for this fragment.
 */
typedef struct Frag Frag;
typedef union Ptrlist Ptrlist;
struct Frag {
    State *start;
    Ptrlist *out;
};

/* Initialize Frag struct. */
Frag frag(State *start, Ptrlist *out) {
    Frag n = {start, out};
    return n;
}

/*
 * Since the out pointers in the list are always
 * uninitialized, we use the pointers themselves
 * as storage for the Ptrlists.
 */
union Ptrlist {
    Ptrlist *next;
    State *s;
};

/* Creat singleton list containing just outp. */
Ptrlist *list1(State **outp) {
    Ptrlist *l = (Ptrlist *) outp;
    l->next = NULL;
    return l;
}

/* Patch the list of states at out to point to start. */
void patch(Ptrlist *l, State *s) {
    Ptrlist *next;
    for (; l; l = next) {
        next = l->next;
        l->s = s;
    }
}

/* Join the two lists l1 and l2, returning the combination. */
Ptrlist *append(Ptrlist *l1, Ptrlist *l2) {
    Ptrlist *oldl1 = l1;
    while (l1->next) {
        l1 = l1->next;
    }
    l1->next = l2;
    return oldl1;
}

/* Convert postfix regular expression to NFA.
 * Return start state. */
State *post2nfa(char *postfix) {
    char *p = postfix;
    Frag stack[1000], *stackp = stack, e1, e2, e;
    State *s;

    if (postfix == NULL) {
        return NULL;
    }

#define push(s) *stackp++ = s
#define pop() *--stackp

    for (; *p; p++) {
        switch (*p) {
            default:
                s = state(*p, NULL, NULL);
                push(frag(s, list1(&s->out)));
                break;
            case CATENATE_SYMB:   /* catenate */
                e2 = pop();
                e1 = pop();
                patch(e1.out, e2.start);
                push(frag(e1.start, e2.out));
                break;
            case '*':   /* zero or more */
                e = pop();
                s = state(Split, e.start, NULL);
                patch(e.out, s);
                push(frag(s, list1(&s->out1)));
                break;
        }
    }

    e = pop();
    if (stackp != stack) {
        return NULL;
    }

    patch(e.out, &matchstate);
    return e.start;

#undef pop
#undef push
}

typedef struct List List;
struct List {
    State **s;
    int n;
};
List l1, l2;
static int listid = 0;

void addstate(List *l, State *s);

void step(List *clist, int c, List *nlist);

/* Compute initial state list */
List *startlist(State *start, List *l) {
    l->n = 0;
    listid++;
    addstate(l, start);
    return l;
}

/* Check whether state list contains a match. */
int ismatch(List *l) {
    int i;
    for (i = 0; i < l->n; i++) {
        if (l->s[i] == &matchstate) {
            return 1;
        }
    }
    return 0;
}

/* Add s to l, following unlabeled arrows. */
void addstate(List *l, State *s) {
    if (s == NULL || s->lastlist == listid) {
        return;
    }
    s->lastlist = listid;
    if (s->c == Split) {
        /* follow unlabeled arrows */
        addstate(l, s->out);
        addstate(l, s->out1);
    } else {
        l->s[l->n++] = s;
    }
}

/*
 * Step the NFA from the states in clist
 * past the character c,
 * to create next NFA state set nlist.
 */
void step(List *clist, int c, List *nlist) {
    int i;
    State *s;

    listid++;
    nlist->n = 0;
    for (i = 0; i < clist->n; i++) {
        s = clist->s[i];
        if (s->c == '.' || s->c == c) {
            addstate(nlist, s->out);
        }
    }
}

/* Run NFA to determine whether it matches s. */
int _match(State *start, char *s) {
    int c;
    List *clist, *nlist, *t;

    clist = startlist(start, &l1);
    nlist = &l2;
    for (; *s; s++) {
        c = *s & 0xFF;
        step(clist, c, nlist);
        t = clist;
        clist = nlist;
        nlist = t;
    }
    return ismatch(clist);
}

bool isMatch(char *s, char *re) {
    if (strlen(re) == 0) {
        return strlen(s) == 0;
    }

    char *post;
    State *start;

    _states_cur_ptr = _states;
    l1.s = _ptrstates;
    l2.s = _ptrstates + 128;

    post = re2post(re);
    if (post == NULL) {
        fprintf(stderr, "bad regexp %s\n", re);
        return 1;
    }

    start = post2nfa(post);
    if (start == NULL) {
        fprintf(stderr, "error in post2nfa %s\n", post);
        return 1;
    }
