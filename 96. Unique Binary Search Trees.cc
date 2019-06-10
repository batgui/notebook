#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
    	if (n == 0 || n == 1) return 1;
    	if(up.find(n) != up.end()) return up[n];
    	auto res = 0;
        for (int i = 1; i <= n; i++) {
        	cout << res << '\n';
        	res += numTrees(i - 1) * numTrees(n - i);
        }
        up[n] = res;
        return res;
    }
private:
	unordered_map<int, int> up;
};



int main(int argc, char *argv[])
{
  Solution *s = new Solution();
  s->numTrees(3);
}



class Solution {
public:
    int numTrees(int n) {
        vector<int> vec(n + 1,0);
        vec[0] = 1;
        vec[1] = 1;
        for(int i = 2; i <= n； i++) {
            for(int j = 1; j <= i; j ++)
                vec[i] = vec[j - 1] * vec[i - j];

        }
        return G[n];
    }
};