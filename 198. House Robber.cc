class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return NULL;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);
    	int robbef = nums[0]; 
    	int robcur = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
        	auto temp = robcur;
        	robcur = max(robbef + nums[i], robcur);
        	robbef = temp;
        }
        return max(robbef, robcur);
    }
};



class Solution {
public:
    int rob(vector<int>& nums) {
  		_size = nums.size();
  		vector <vector <int>> vec(_size + 1, vector<int>(2, 0));
  		for (int i = 1; i <= nums.size(); i++) {
  			vec[i][0] = max(vec[i - 1][0], vec[i - 1][1]);
  			vec[i][1] = nums[i - 1] + vec[i - 1][0]; 
  		}
  		return max(vec[_size][0], vec[_size][1]);
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        _size = nums.size();
        prevNo = 0;
        prevYes = 0;
        for(auto n : nums) {
        	auto temp = prevNo;
        	prevNo = max(prevNo, prevYes);
        	prevYes = n + temp;
        }
        return max(prevNo, prevYes);
    }
};



1.Find recursive relation
2.Recursive (top-down)
3.Recursive + memo (top-down)
4.Iterative + memo (bottom-up)
5.Iterative + N variables (bottom-up)


class Solution {
public:
    int rob(vector<int>& nums) {
    	return rob(nums, nums.size());

    }
    int rob(vector<int>& nums, int n ) {
    	if(n <= 0) {
    		return 0;
    	}
    	return max(nums[n - 1] + rob(nums, n - 2), rob(nums, n - 1));
    }

};


class Solution {
public:
    int rob(vector<int>& nums) {
    	auto _size = nums.size();
        memo = vector<int>(_size + 1, -1);
    	return rob(nums, _size);

    }
    int rob(vector<int>& nums, int n ) {
    	if(n <= 0) {
    		return 0;
    	}
    	if (memo[n] != 0) return memo[n];
    	res = max(nums[n - 1] + rob(nums, n - 2), rob(nums, n - 1));
    	memo[n] = res;
    	return memo[n];
    }
private:
	vector<int> memo;

};


class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == NULL) return NULL;
  		auto _size = nums.size();
  		memo = vector<int>(_size + 1, -1);
  		memo[0] = 0;
  		memo[1] = nums[0];
  		for (int i = 2; i <= _size; i++) {
  			memo[i] = max(memo[i-1], memo[i - 2] + nums[i-1]);
  		}
  		return memo[_size];


    }
private:
	vector<int> memo;    

}


class Solution {
public:
    int rob(vector<int>& nums) {
    	if(nums.size() == NULL) return NULL;
  		auto _size = nums.size();
  		
  		auto pre = 0;
  		auto now = nums[0];
  		for (int i = 2; i <= _size; i++) {
  			auto temp = now;
  			now = max(now, pre + nums[i - 1]);
  			pre = temp;
  		}
  		return now;


    }
private:
	vector<int> memo;    
};