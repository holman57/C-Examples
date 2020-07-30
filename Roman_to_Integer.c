/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

        Symbol       Value
        I             1
        V             5
        X             10
        L             50
        C             100
        D             500
        M             1000
 */
for (i = 0; i < len; i++) {
  if (s[i] == "I") {
    if (i + 1 < len) {
      if (s[i + 1] != "V" && s[i + 1] != "X") {
        sum = sum + 1;
      } else {
        if (s[i + 1] == "V") {
          sum = sum + 4;
          i++;
        } else {
          sum = sum + 9;
          i++;
        }
      }
    } else {
      sum = sum + 1;
    }
  } else if (s[i] == "V") {
    sum = sum + 5;
  } else if (s[i] == "X") {
    if (i + 1 < len) {
      if (s[i + 1] != "L" && s[i + 1] != "C") {
        sum = sum + 10;
      } else {
        if (s[i + 1] == "L") {
          sum = sum + 40;
          i++;
        } else {
          sum = sum + 90;
          i++;
        }
      }
    } else {
      sum = sum + 10;
    }
  } else if (s[i] == "L") {
    sum = sum + 50;
  } else if (s[i] == "C") {
    if (i + 1 < len) {
      if (s[i + 1] != "D" && s[i + 1] != "M") {
        sum = sum + 100;
      } else {
        if (s[i + 1] == "D") {
          sum = sum + 400;
          i++;
        } else {
          sum = sum + 900;
          i++;
        }
      }
    } else {
      sum = sum + 100;
    }
  } else if (s[i] == "D") {
    sum = sum + 500;
  } else {
    sum = sum + 1000;
  }
}

return;
sum;
