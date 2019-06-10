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
    int n; // hang
    int m; // lie
    int ret = 1;

    scanf("%d", &n);
    scanf("%d", &m);

    vector <vector<int>> a(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 1) {
                int left = j == 0? 0: a[i][j-1];
                int up   = i==0? 0: a[i-1][j];
                int leftup = ((i==0||j==0)? 0: a[i-1][j-1]);
                int rightup = ((i==0||j==m-1)? 0: a[i-1][j+1]);
                int mymax1 = max(leftup, rightup);
                int mymax2 = max(left, up);
                int mymax = max(mymax1, mymax2);
                if (mymax == 0) a[i][j] = ret++;
                else a[i][j] = mymax;
            }
        }
    }


    cout << ret-1 << endl;

    return 0;
}