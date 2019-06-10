class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
    	if (envelopes.size() == 0) return 0;
        auto n = envelopes.size();
      	vector<int> res;  
        sort(envelopes.begin(), envelopes.end(), [](pair<int, int> a, pair<int, int> b) {
        	if (a.first == b.first) return a.second > b.second;
        	return a.first < b.first;
        });
       	
       	for (auto v : envelopes) {
       		auto iter = lower_bound(res.begin(), res.end(), v.second);
       		if (iter == res.end()) 
       			res.push_back(v.second);
       		else
       			*iter = v.second;
       	}
       	return res.size();

    }


    
};