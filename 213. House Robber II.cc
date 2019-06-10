class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == NULL) return NULL;
    	if (nums.size() == 1) return nums[0];
		auto prevNo = 0;
		auto prevYes = 0;
		for(int i = 0; i < nums.size() - 1; i++) {
			auto temp = prevNo;
			prevNo = max(prevNo, prevYes);
			prevYes = temp + nums[i];
		}
		auto temp1 = max(prevNo, prevYes);
		prevNo = 0;
		prevYes = 0;
		for(int i = 1; i < nums.size(); i++) {
			auto temp = prevNo;
			prevNo = max(prevNo, prevYes);
			prevYes = temp + nums[i];
		}
		auto temp2 = max(prevNo, prevYes);
		return max(temp2, temp1);
		}		        
    

};

class Solution {
public:
    int rob(vector<int>& nums) {
		auto prevNo = 0;
		auto prevYes = 0;
		for(int i = 0; i < nums.size() - 1; i++) {
			prevNo = max(prevNo, prevYes);
			prevYes = prevNo + nums[i];
		}
		auto temp1 = max(prevNo, prevYes);
		auto prevNo = 0;
		auto prevYes = 0;
		for(int i = 1; i < nums.size(); i++) {
			prevNo = max(prevNo, prevYes);
			prevYes = prevNo + nums[i];
		}
		auto temp2 = max(prevNo, prevYes);
		return max(temp2, temp1);
		}		        
    

};