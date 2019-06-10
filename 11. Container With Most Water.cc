	class Solution {
	public:
	    int maxArea(vector<int>& height) {
	        int lo = 0;
	        int hi = height.size() - 1;
	        int MostWater = 0;
	        while (lo < hi) {
	        	MostWater = max(MostWater, (hi - lo) * min(height[lo], height[hi]));
	        	if (height[lo] > height[hi])
	        		hi --;
	        	else lo ++;

	        }
	        return MostWater;

	    }
	};