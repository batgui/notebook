class Solution {
public:
    long findKthNumber(int n, int k) {
    	long cur = 1;
    	
    	while (k > 1) {
    		long steps = calcSteps(cur, cur + 1, n);
    		if (steps < k) {
    			cur += 1;
    			k -= steps;
    		}
    		else {
    			k -= 1;
    			cur *= 10;
    		}

    	}
    	return cur;

    }

    long calcSteps(long now, long next, long n) {
    	long steps = 0;
    	while (now <= n) {

    		steps += min(n + 1, next) - now;
    		next *= 10;
    		now *= 10;

    	}
    	return steps;
    }
};