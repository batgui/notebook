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




int DEL = 999999;
int main(int argc, const char * argv[]) {
    int n;
    cin >> n,m;
    int ret = 0;
    vector <int> a(n, 0);
    vector <int> b(n, 0);
    vector <int> c(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i] - 1;
    }

    for (int i = 0; i < m; ++i) {
        
        if (a[b[i]] > 0)
            a[b[i]] --;
            b[i] = DEL;
        
    }
    for (int i = 0; i < m; ++i) {
        if (b[i] != DEL) {
            c.push_back(b[i]);
        }
    }


    cout << ret << endl;
    
    return 0;
}