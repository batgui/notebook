class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for (int i = 0; i < nums.size(); i ++) {
        	for (int j = i + 1; j < nums.size(); j++) {
        		auto aim = target - nums[i] - nums[j];
        		int k = j + 1;
        		int o = nums.size() - 1;
        		while (k < o) {
        			if (nums[k] + nums[o] == aim ) {
        				res.push_back({nums[i], nums[j], nums[k], nums[o]});
        				while (k < o && nums[k] == nums[k + 1]) k++;
        				while (k < o && nums[o] == nums[o - 1]) o--;
        				k++;
        				o--;
        			}
        			else if (nums[k] + nums[o] < aim) {
        				k++;
        			}
        			else
        				o--; 
        		}
        		while(j < nums.size() && nums[j] == nums[j + 1]) j ++;
        	}
        	while(i < nums.size() && nums[i] == nums[i + 1]) i ++;
        }
        return res;
    }
};