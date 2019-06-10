class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    	typedef pair<int, int> pi;
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        priority_queue<pi> pqp;
        for(int i = 0; i < Capital.size(); i++) {
        	pq.push(make_pair(Capital[i], Profits[i]));
        }
        while(k --) {
        	while (!pq.empty() && pq.top().first <= W) {
                pi rec = pq.top();
                pq.pop();
                
        		pqp.push(make_pair(rec.second, rec.first));
        	}
        	if(!pqp.empty()) {
        		W += pqp.top().first;
        		pqp.pop();
        	}

        }
        return W;
    }
};


class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        priority_queue<int> pq;
        multiset<pair<int ,int>> ms;
        for(int i = 0; i < Profits.size(); i++) {
        	if (Capital[i] <= W) {
        		pq.push(Profits[i]);

        	}
        	else {
        		ms.emplace(Capital[i], Profits[i]);
        	}
        }
        	while(k--) {
        		if(!pq.empty()) {
        			W += pq.top();
        			pq.pop();
        		}
        		for(auto i = ms.begin(); ms.size() && i->first <= W; i = ms.erase(i)) pq.push(i-> second);
        	}
        
        return W;
    }
};