/*
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * */
bool isValid(char *s) {
    int SIZE = strlen(s);
    char *ParenStack = (char *) calloc(SIZE, sizeof(char));
    int i, LastStackIndex;
    int StackIndex = 0;

    for (i = 0; i < SIZE; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            ParenStack[StackIndex] = s[i];
            StackIndex++;
        } else {
            if (!StackIndex) {
                return 0;
            }
            LastStackIndex = StackIndex - 1;
            switch (s[i]) {
                case ')':
                    if (ParenStack[LastStackIndex] == '(') {
                        ParenStack[LastStackIndex] = '\0';
                        StackIndex--;
                    } else {
                        return 0;
                    }
                    break;
                case ']':
                    if (ParenStack[LastStackIndex] == '[') {
                        ParenStack[LastStackIndex] = '\0';
                        StackIndex--;
                    } else {
                        return 0;
                    }
                    break;
                case '}':
                    if (ParenStack[LastStackIndex] == '{') {
                        ParenStack[LastStackIndex] = '\0';
                        StackIndex--;
                    } else {
                        return 0;
                    }
                    break;
            }
        }
    }
    if (ParenStack[0] == '\0') {
        return 1;
    } else {
        return 0;
    }
}