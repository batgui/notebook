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
	priority_queue <int> pq;
	int count = 0;
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {

        if(stations.empty()) {
        	//cout << 111 <<endl;
        	return startFuel >= target ? 0 : -1;
        }
        int i = 0;
        while(1) {
        	if (startFuel >= target)
        		return count;
        	while(i < stations.size() && stations[i][0] <= startFuel) {
        		pq.push(stations[i][1]);
        		i ++;
        	}
        	if (pq.empty()) return -1;
        	startFuel += pq.top();
        	pq.pop();
        	count++;
        }
        return count;
    }
};


int main(int argc, const char * argv[]) {
    int target = 100, startFuel = 10;
    //vector<vector<int>> stations = {{10,60},{20,30},{30,30},{60,40}};
    vector<vector<int>> stations{};
    Solution* s = new Solution();
    
    //auto ans = s->minRefuelStops(target, startFuel, stations);
    auto ans = s->minRefuelStops(100, 1, stations);
	cout << ans << endl;
    return 0;
}