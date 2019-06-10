class Solution {
set<int> mem;

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        return DFS(s, 0, wordDict);

    }
private: 
	bool DFS(string s, int index, vector<string>& wordDict) {
		if (index == s.size())
			return true;
		if (mem.find(index) != mem.end())
			return false;
        for (int i = index + 1; i < s.size(); i++) {
        	string str = s.substr(index, i - index);
        	if (find(wordDict.begin(), wordDict.end(), str) != wordDict.end()) {
        			
        			if (DFS(s, i, wordDict)) {
        				return true;
        			}
        			else
        				mem.insert(i);

        		
        	}
        }
        mem.insert(index);
        return false;
	}
};


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
    	if(s.size() == 0) return false;
    	vector<int> dp(s.size() + 1, false);
    	dp[0] = true;
    	for (int i = 1; i <= s.size(); i ++) {
    		for (int j = i - 1; j > 0; j --) {
    			if (dp[j]) {
    				string str = s.substr(j, i - j);
    				if (find(wordDict.begin(), wordDict.end(), str) != wordDict.end()) {
    					dp[i] = true;
    					break;
    				}
    			}
    		dp[i] = false;
    		}
    	}
    return dp[s.size()];
    }
};