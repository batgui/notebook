class NumArray {
public:
    NumArray(vector<int>& nums) {
    	int n = nums.size();
        vector<int> d(n,0);
        if (nums.size() > 0) 
        	d[0] = nums[0];
        for(int  i = 1; i < nums.size(); i++ ) {
        	d[i] = d[i - 1] +  nums[i];

        }
        c = d;
    }
    
    int sumRange(int i, int j) {

    	if (i == 0) {
    		return c[j];
    	}
        return c[j] - c[i - 1];
    }
private:
	vector<int> c;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */