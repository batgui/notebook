#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;


class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

    	auto flag = 1;
    	if ((divisor > 0) ^ (dividend > 0)) {
    		flag = -1;

    	}
    	long dvd = labs(dividend);
    	long dvs = labs(divisor);
    	//cout << dvd << '\n';
    	//cout << dvs << '\n';
    	long ans = 0;
    	while(dvd >= dvs) {
			long tmp = dvs, m = 1;
			while (tmp << 1 <= dvd) {
				tmp <<= 1;
				m <<= 1;
			}
			dvd -= tmp;
			ans +=m;
		}
    	return flag * ans;
    	
    }
};


int main(int argc, char *argv[])
{
  Solution *s = new Solution();
  s->divide(2147483647, 1);
}