class NumArray {
vector<int> d(nums.size() + 1, 0);	
public:
    NumArray(vector<int>& nums) {
        
        for (int i = 0; i < d.size(); i++) {
        	d[i + 1] = d[i] + nums[i];
        }
    }
    
    void update(int i, int val) {
        
    }
    
    int sumRange(int i, int j) {
        return d[j + 1] - d[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */