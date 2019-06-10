class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int maxWeight = 0;
        int upperBound = 0;
        for (auto &w : weights) {
        	if (w > maxWeight)
        		maxWeight = w;
        	upperBound += w;
        }
        while (maxWeight < upperBound) {
        	
        	int days = 1;
        	int localWeight = 0;
        	int mid = (maxWeight + upperBound) / 2;
        	for (auto &w : weights) {
        		localWeight += w;
        		if (localWeight > mid) {
        			days ++;
        			localWeight = w;
        		}

        	}
        	if (days > D) maxWeight = mid + 1;
        	if (days <= D) upperBound = mid;
        }
        return maxWeight;
    }
};