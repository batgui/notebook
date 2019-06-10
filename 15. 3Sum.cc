class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
    	sort(nums.begin(), nums.end());
    	vector<vector<int>> res;
        for (int i = 0; i < nums.size(); i++) {
        	  	
        	auto target = - nums[i];
        	int j = i + 1;
        	int k = nums.size() - 1;
        	
        	while (j < k) {
        		if (nums[j] + nums[k] == target) {
        			
        			
        			res.push_back({nums[i], nums[j], nums[k]}); 
        			while(j < k && nums[j] == nums[j + 1]) j++;
        			while(k > j && nums[k] == nums[k - 1] ) k--;
        			j++;
        			k--;
        			
        		}
        		else if (nums[j] + nums[k] < target) {       			
        			j++;
        		}
        		else {        			
        			k--;
        		}
        	}	
			while (i + 1 < nums.size() && nums[i] == nums[i + 1]) i++;
        }
        return res;
    }
};


