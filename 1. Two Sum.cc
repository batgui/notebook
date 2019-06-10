#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <tuple>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <ctime>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <numeric>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
    	unordered_map <int, int> umap;
    	for (int i = 0; i < nums.size(); i ++) {
    		if (umap.find(target - nums[i]) == umap.end())
    			umap[nums[i]] = i;
    		else
    			return vector<int>{umap[target - nums[i]], i};
    	}
    return -1;
    }
};

int main(int argc, const char * argv[]) {
    int target = 9;
    vector <int > vec{2, 7, 11, 15};
    Solution* s = new Solution();
    vector<int> ans = s->twoSum(vec, target);
    for (auto &a : ans) {
    	cout << a << " ";
    }
    return 0;
}