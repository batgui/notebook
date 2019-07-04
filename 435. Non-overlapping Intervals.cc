class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(),[&](const vector<int >&a, const vector<int> &b){return a[1] < b[1];});
        auto count = -1;
        auto lastPoint = intervals[0][1];
        for (auto & i : intervals) {
        	if (i[0] < lastPoint) {
        		count++;
        		if (i[1] < lastPoint) lastPoint = i[1];
        	}
        	else 
        		lastPoint = i[1];
        }
        return count;

    }
};

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(),[&](const vector<int >&a, const vector<int> &b){return a[1] < b[1];});
        auto count = 1;
        auto lastPoint = intervals[0][1];
        for (auto & i : intervals) {
        	if (i[0] >= lastPoint) {
        		count++;
        		lastPoint = i[1];
        	}

        }
        return intervals.size() - count;

    }
};