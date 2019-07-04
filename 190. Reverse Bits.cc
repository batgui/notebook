class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
		int res = 0;

		for (int i = 0; i < 32; i ++) {
			int temp = n % 2;

            
			n /= 2;
            res <<= 1;
			res = (res + temp);
            
		}
		return res;
    }
};