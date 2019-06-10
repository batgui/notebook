class Solution {
    public int[] searchRange(int[] nums, int target) {
        int[] targetrange = {-1, -1};
        int leftIdx = extremeInsertIndex(nums, target, true);
        if (leftIdx == nums.length || nums[leftIdx] != target) {
            return targetrange;
        }
        targetrange[0] = leftIdx;
        targetrange[1] = extremeInsertIndex(nums, target, false);
        return targetrange;
    }



    private int extremeInsertIndex(int[] nums, int target, boolean left) {
      int lo = 0;
      int hi = nums.length;
      while ( lo < hi) {
        int mid = lo + ((hi - lo) >> 1);
        if (nums[mid] < target || ) {
            lo = mid + 1;
        } 
        else hi = mid;   
        
    }
return lo;

}
}