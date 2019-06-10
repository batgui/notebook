class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {

  		vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
  		for (auto &s : strs) {
  			int zero = 0;
  			int one = 0;
  			for (auto c : s) {
  				if (c == '0') 
  					zero ++;
  				else if (c == '1')
  					one ++;

  			}
  			for (int i = m ; i >=zero ; i--)
  				for (int j = n; j >= one; j--) {
  					dp[i][j] = max(dp[i][j], dp[i - zero][j - one] + 1);
  				}

  		}
  		return dp[m][n];      
    }
};

int findMaxForm(vector<string>& strs, int m, int n) {
  vector<vector<int>> memo(m+1, vector<int>(n+1, 0));
  int numZeroes, numOnes;

  for (auto &s : strs) {
    numZeroes = numOnes = 0;
    // count number of zeroes and ones in current string
    for (auto c : s) {
      if (c == '0')
	numZeroes++;
      else if (c == '1')
	numOnes++;
    }

    // memo[i][j] = the max number of strings that can be formed with i 0's and j 1's
    // from the first few strings up to the current string s
    // Catch: have to go from bottom right to top left
    // Why? If a cell in the memo is updated(because s is selected),
    // we should be adding 1 to memo[i][j] from the previous iteration (when we were not considering s)
    // If we go from top left to bottom right, we would be using results from this iteration => overcounting
    for (int i = m; i >= numZeroes; i--) {
	for (int j = n; j >= numOnes; j--) {
          memo[i][j] = max(memo[i][j], memo[i - numZeroes][j - numOnes] + 1);
	}
    }
  }
  return memo[m][n];
}


//Make a 3D Vector
typedef vector<int> v1d;
typedef vector<v1d> v2d;
typedef vector<v2d> v3d;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int l = strs.size();
        v3d dp(l+1, v2d(m+1, v1d(n+1, 0))); //dp[l+1][m+1][n+1]
        
        for(int i=1;i<=l;i++)
        {
            string s = strs[i-1];
            int ones = count(s.begin(), s.end(), '1');
            int zeros = s.size()-ones;
            
            for (int j=0;j<=m;j++)
            {
                for (int k=0;k<=n;k++)
                {
                    if (j>=zeros && k>=ones)
                        dp[i][j][k] = max(dp[i-1][j][k], 1 + dp[i-1][j-zeros][k-ones] );
                    else
                        dp[i][j][k] = dp[i-1][j][k];
                    
                }//k
            }//j
        }//i
        
        return dp[l][m][n];
    }
};
Reference : @yangluphil and @ZhuEason

3) Knapsack 2D DP Array Solution O (l x m x n)
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    
    for (auto &s: strs) {
        int ones = count(s.begin(), s.end(), '1');
        int zeros= s.size()-ones;
        for (int i=m; i>=zeros; i--) 
            for (int j=n; j>=ones; j--)
                dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones]+1);
    }
    return dp[m][n];
}