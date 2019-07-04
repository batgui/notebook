class Solution {
public:
    bool isUgly(int num) {
     int prev = num;
        while (num != 1) {
         prev = num;
         if (num % 3 == 0) num /= 3;
          if (num % 2 == 0) num /= 2;
         if (num % 5 == 0) num /= 5;
         if (prev == num) {
          return false;
         }
        }
        return true;
    }
};