class Solution {

public:
	vector<vector<int>> schedule; 
	vector<int> indegree;
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
    	int count = 0;
    	schedule = vector<vector<int>>(numCourses);
    	indegree = vector<int>(numCourses, 0);
    	buildGraphAndComputeIndgree( prerequisites);
 		vector<int> res;
   	
    	for (int i = 0; i < numCourses; i ++) {
	    	for (int i = 0; i < indegree.size(); i++) {
	    		if (indegree[i] == 0) {
	    			res.push_back(i);
	    			count ++;
	    			cout << i << endl;
	    			indegree[i] = -1;
	    			for (auto & s : schedule[i]) {
	    				indegree[s] --;
	    			}
	    		}

	    	}
	    }
    	return count == numCourses ? res : vector<int>(0);
    }

    void buildGraphAndComputeIndgree(vector<vector<int>>& prerequisites) {
    	for (auto & p : prerequisites) {
    		schedule[p[1]].push_back(p[0]);
    		indegree[p[0]] ++;
    	}
    }

};
