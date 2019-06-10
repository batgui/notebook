class Solution {
	private Map<Integer, Integer> count(int[] nums) {
		Map<Integer, Integer> m = new HashMap<Integer, Integer>();
		for (int n : nums) {
			if(!m.containsKey(n)) {
				m.put(n, 1);
			}
			else
				m.put(n, m.get(n) + 1);
		}
		return m;
	}

    public int majorityElement(int[] nums) {
        Map<Integer, Integer> hm = count(nums);
    	Map.Entry<Integer, Integer> max = null;
    	for (Map.Entry<Integer, Integer> m : hm.entrySet()) {
    		if (max == null || m.getValue() > max.getValue()) {
    			max = m;
    		}
    	}
    	return max.getKey();
    }
}


class Solution {
	private int countInRange(int[] nums, int lo, int hi, int num) {
		int count = 0;
		
        for (int i = lo; i <= hi; i++) {
            if (nums[i] == num) {
                count++;
            }
         }
		return count;
	}
	private int majorityElementRec(int[] nums, int lo, int hi) {
		if (lo == hi) {
			return nums[lo];
		}
		int mid = lo + (hi - lo) / 2;

		int left = majorityElementRec(nums, lo, mid);
		int right = majorityElementRec(nums, mid + 1, hi);
		if (left == right) 
			return left; 
		int leftc = countInRange(nums, lo, hi, left);
		int rightc = countInRange(nums, lo, hi, right);
		if(leftc > rightc)
			return left;
		return right;
	}
    public int majorityElement(int[] nums) {
        return majorityElementRec(nums, 0, nums.length - 1);
    }
}