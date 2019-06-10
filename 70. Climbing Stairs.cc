class Solution {
public:
    int climbStairs(int n) {
        if (n < 3) {
        	return n;
        }
        int sum = 0;
        int prev = 1;
        int cur = 2;
        for (int i = 3; i < n; i++) {
        	sum = prev + cur;
        	prev = cur;
        	cur = prev;

        }
        return sum;
    }
};