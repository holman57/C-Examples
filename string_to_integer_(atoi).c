int isInt(char curChar){
    int cur = curChar;
    return cur >= 48 && cur <= 57;
}

int isWhitespaceOrDash(char curChar){
    return curChar == ' ' || curChar == '-' || curChar == '+';
}

int isAcceptableChar(char curChar){
    return isInt(curChar) || isWhitespaceOrDash(curChar);
}

int calculateAnswer(int answer, int isNegative){
    if(isNegative < 0){
        return -1 * answer;
    }
    return answer;
}

int myAtoi(char * str){
    if(!strlen(str)){
        return 0;
    }
    long answer = 0;
    int isNegative = 1;
    int isSigned = 0;
    int visitedNum = 0;
    int i = 0;
    char cur = str[i];
    while(cur && isAcceptableChar(cur)){
        if(isWhitespaceOrDash(cur)){
            if(visitedNum){
                return answer;
            }
            if(isSigned){
                return 0;
            }
            if(cur == '-'){
                if (isNegative < 0 || answer != 0){
                    return answer;
                }
                isNegative = -1;
                isSigned = 1;
            } else if(cur == '+'){
                isSigned = 1;
            }
        } else {
            visitedNum = 1;
            int curInt = (cur - 48) * isNegative;
            answer = (answer * 10) + (curInt);
            if(isNegative < 0 && answer < INT_MIN){
                return INT_MIN;
            }
            if(isNegative > 0 && answer > INT_MAX){
                return INT_MAX;
            }
            
        }     
        i += 1;
        cur = str[i];
    }
    return answer;
}