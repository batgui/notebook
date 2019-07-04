class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {
    	long lcm = A * B / __gcd(A, B);
    	long l = 1;
    	long r = 1e15;
    	long mod = 1e9 + 7;
    	while (l < r) {
    		long  mid = (l + r) / 2;

    		if (mid / A + mid / B - mid / lcm < N) {
    			l  = mid + 1;
    		}
    		else r = mid;
    	}
    	return r % mod;

    }
};