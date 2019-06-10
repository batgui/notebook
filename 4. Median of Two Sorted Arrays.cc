
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    	if (nums1.size() > nums2.size() ) 
    		return findMedianSortedArrays(nums2, nums1);
    	auto m = nums1.size();
    	auto n = nums2.size();
    	int lo = 0, hi = m, halfLen = (m + n + 1) / 2;
    	while (lo <= hi) {
    		auto i = (lo + hi) / 2;
    		auto j = halfLen - i;
    		//当i等于m时，j可能为0，nums2[j - 1]不存在
    		if (i < m && nums1[i] < nums2[j - 1] )
    			lo = i + 1;
    		//当i等于0时，nums1[i - 1]不存在
    		else if (i > 0  && nums1[i - 1] > nums2[j])
    			hi = i - 1;
    		else{

    			int leftMax = 0;
    			int rightMin = 0;
    			//先求左边的最大值，如果m + n为奇数，则左边的最大值就是中位数，直接返回
    			if (i == 0) {
    				leftMax = nums2[j - 1];
    			}
    			else if (j == 0) {
    				leftMax = nums1[i - 1];
    			}
    			else {
    				leftMax = max(nums1[i - 1], nums2[j - 1]);
    			}
    			if ((m + n) % 2 == 1)
    				return leftMax;
    			//求右边的最大值
    			if (i == m) {
    				rightMin = nums2[j];
    			}
    			else if (j == n) {
    				rightMin = nums1[i];
    			}
    			else {
    				rightMin = min(nums2[j], nums1[i]);
    			}
    			return (leftMax + rightMin) / 2.;
    		}
    	}
    	return -1;
    }
};