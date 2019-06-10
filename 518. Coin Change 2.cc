class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int > dp(amount + 1, 0);
        dp[0] = 1;
        for (auto &c : coins) {
        	for (int i = 1; i <= amount; i ++) {
        		if (i >= c) {
        			dp[i] += dp[i - c];
        		}
        	}
        }
        return dp[amount];
    }
};

这道题用动态规划做。

组成amount大小的硬币的组合数等于组成amount - c(for c in coins)之和。

也就是dp[i] += dp[i - c];




