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

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    vector <int> a(n, 0);
    int ret = 0;
    int mymax = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    // a[j] - j + a[i] + i
    mymax = a[0] + 0;
    for (int i = 1; i < n; ++i) {
        
        ret = max(mymax + a[i] - i, ret);

        mymax = max(a[i]+i, mymax);
    }

    cout << ret << endl;
    
    return 0;
}