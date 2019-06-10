class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        
        return lengthOfLIS(nums, INT_MIN, 0);
    }
    int ret;
    int lengthOfLIS(vector<int>& nums, int prev, int curpos) {
    	
    	if (curpos == nums.size()) {
    		return 0;
    	}
    	int taken = 0 ;
    	if (nums[curpos] > prev) {
    		taken =  1 + lengthOfLIS(nums, nums[curpos], curpos + 1);
    	}

  		int notaken = lengthOfLIS(nums, prev, curpos + 1);
    	return ret = max(taken, notaken);
    }
};



class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
    	auto n = nums.size();
 	 	vector<vector<int>> memo(n, vector<int>(n + 1, 0));      
        return lengthOfLIS(nums, -1, 0,  memo);
    }

    int lengthOfLIS(vector<int>& nums, int prepos, int curpos, vector<vector<int>>& memo) {
    	if (curpos == nums.size()) {
    		return 0;
    	}
    	if (memo[curpos][prepos + 1] > 0) {
    		return memo[curpos][prepos];
    	}

    	int taken = 0 ;
    	if (prepos < 0 || nums[curpos] > nums[prepos] ) {
    		taken =  1 + lengthOfLIS(nums, curpos, curpos + 1, memo);
    	}

  		int notaken = lengthOfLIS(nums, prepos, curpos + 1, memo);
    	return memo[curpos][prepos + 1] = max(taken, notaken);
    }




};


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<int> vec(n, 1);
        Max = 0;
        for (int i = 1; i < nums.size(); i++) {
        	for (int j = 0; j < i; j ++) {
        		if (nums[i] > nums[j]) {
        			vec[i] = max(vec[i], vec[j] + 1);
        			Max = max(Max, vec[i]);
        		}
        	}
        }
        return Max;
    }
};


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
    auto n = nums.size();
    // vector<vector<int>> memo(n, vector<int>(n + 1, 0));      
    vector<vector<int>> memo(n+1, vector<int>(n, -1));

        return lengthOfLIS(nums, -1, 0,  memo);
    }

    int lengthOfLIS(vector<int>& nums, int prepos, int curpos, vector<vector<int>>& memo) {
     if (curpos == nums.size()) {
      return 0;
     }
     if (memo[prepos + 1][curpos] >= 0) {
       return memo[prepos+1][curpos];
     }

     int taken = 0 ;
     if (prepos < 0 || nums[curpos] > nums[prepos] ) {
      taken =  1 + lengthOfLIS(nums, curpos, curpos + 1, memo);
     }

    int notaken = lengthOfLIS(nums, prepos, curpos + 1, memo);
     return memo[prepos+1][curpos] = max(taken, notaken);
    }




};



class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
    	auto n = nums.size();
 	 	vector<vector<int>> memo(n, vector<int>(n + 1, -1));      
        return lengthOfLIS(nums, -1, 0,  memo);
    }

    int lengthOfLIS(vector<int>& nums, int prepos, int curpos, vector<vector<int>>& memo) {
    	if (curpos == nums.size()) {
    		return 0;
    	}
    	if (memo[curpos][prepos + 1] >= 0) {
    		return memo[curpos][prepos + 1];
    	}

    	int taken = 0 ;
    	if (prepos < 0 || nums[curpos] > nums[prepos] ) {
    		taken =  1 + lengthOfLIS(nums, curpos, curpos + 1, memo);
    	}

  		int notaken = lengthOfLIS(nums, prepos, curpos + 1, memo);
    	return memo[curpos][prepos + 1] = max(taken, notaken);
    }




};

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        
        
        dfs(nums, -1, 0);
        
        return ret;
    }

private:
    int ret = 0;
    
    void dfs(vector<int> &nums, int prevIndex, int localLen)
    {
        if ( localLen + nums.size() - prevIndex - 1  < ret) return;
        else {
            for (int i = prevIndex+1; i < nums.size(); ++i) {
                if (prevIndex != -1 && nums[i]-nums[prevIndex] <= 0) continue;
                
                dfs(nums, i, localLen+1);
            }
            ret = max(ret, localLen);
        }
    }
};