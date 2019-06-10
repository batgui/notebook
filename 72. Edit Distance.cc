class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i ++) {
        	dp[i][0] = i;
        } 
        for (int j = 1; j <= n; j ++) {
        	dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
        	for (int j = 1; j <= n; j++) {
        		if (word1[i - 1] == word2[j - 1]) {
        			dp[i][j] = dp[i - 1][j - 1];
        		}
        		else {
        			dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;        		}
        	}
        }
    return dp[m][n];
    }
};


class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        int pre;
        vector<int > cur(n + 1, 0);
        for (int j = 1; j <= n; j++) {
        	cur[j] = j;
        }

        for (int i = 1; i <= m; i++) {
        	pre = cur[0];
        	cur[0] = i;
        	for (int j = 1; j <= n; j++) {
        		int temp = cur[j];
        		if (word1[i - 1] == word2[j - 1]) {
        			cur[j] = pre;
        		}
        		else {
        			cur[j] = min(cur[j], min(pre, cur[j - 1])) + 1;

        		}
        		pre = temp;

        	}
        }
        return cur[n];

    }
};