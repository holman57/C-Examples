char ** fizzBuzz(int n, int* returnSize) 
{
    *returnSize = n;
    char** answer;
    answer = malloc(n * sizeof(char*));
    for (int i = 1; i < n + 1; i++) 
    {
        char* s;
        if (i % 15 == 0) 
        {
            answer[i - 1] = strdup("FizzBuzz");
        } 
        else if (i % 5 == 0) 
        {
            answer[i - 1] = strdup("Buzz");
        } 
        else if (i % 3 == 0) 
        {
            answer[i - 1] = strdup("Fizz");
        } 
        else 
        {
            int length = snprintf(NULL, 0, "%d", i);
            char* i_str = malloc(length + 1);
            snprintf(i_str, length + 1, "%d", i);
            answer[i - 1] = i_str;
        }
    }
    return answer;
}
