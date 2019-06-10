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


int main(){
    int m,n;
    // cin >> m;
    // cin >> n;
    m = 4;
    n = 6;


    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> visit(m + 1, vector<int>(n + 1, 0));
    dp[0][0] = 0;
    visit[0][0] = 0;
    int temp = 1;
    int j = 2;
    for(int i = 1; i <= m; i++) {        
        if(i >= temp) {
            dp[i][0] = dp[i - 1][0] + 1;

            temp = temp + j++;
            //cout << "temp " << temp << endl;
        }



        else
            dp[i][0] = dp[i - 1][0];


    } 
    j = 2;
    //cout << dp[m][0] << endl;
    for(int i = 0; i <= n; i++) {
        
        if(i >= temp) {
            dp[0][i] = dp[0][i - 1] + 1;
            temp = temp + j++;
            //cout << temp << endl;
        }
        else
            dp[0][i] = dp[0][i - 1];
        
    }
    
    temp = 1;
    
    for (int i = 1; i <= m; i++) {
        j = 2;
        for (int j = 1; j <= n; j++) {
            if(i >= temp || j >= temp) {
                if (i >= temp)
                    dp[i][j] = max(dp[i - temp][j], dp[i][j]);
                if (j >= temp)
                    dp[i][j] = max(dp[i][j - temp], dp[i][j]);
                temp = temp + j++;
                visit[i][j] = 1;
            }
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    int res = dp[m][n];
    int count = 0;
    for(int i = 0; i <= m; i++)
        if (visit[i][n] && dp[i][n] == res)
            count ++;
    for(int j = 0; j <= n; j++)
        if (visit[m][j] && dp[m][j] == res)
            count ++;    
    cout << res << endl;
    cout << count << endl;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << dp[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << visit[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}