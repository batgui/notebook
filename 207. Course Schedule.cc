class Solution {

public:
	vector<vector<int>> schedule; 
	vector<int> indegree;
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    	int count = 0;
    	schedule = vector<vector<int>>(numCourses);
    	indegree = vector<int>(numCourses, 0);
    	buildGraphAndComputeIndgree( prerequisites);
    	for (int i = 0; i < numCourses; i ++) {
	    	for (int i = 0; i < indegree.size(); i++) {
	    		if (indegree[i] == 0) {
	    			count ++;
	    			cout << i << endl;
	    			indegree[i] = -1;
	    			for (auto & s : schedule[i]) {
	    				indegree[s] --;
	    			}
	    		}

	    	}
	    }
    	return count == numCourses;
    }

    void buildGraphAndComputeIndgree(vector<vector<int>>& prerequisites) {
    	for (auto & p : prerequisites) {
    		schedule[p[1]].push_back(p[0]);
    		indegree[p[0]] ++;
    	}
    }

};



class Solution {
public:
	vector<vector<int>> schedule;
	vector<int> visiting;
	vector<int> visited;
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        schedule = vector<vector<int>>(numCourses);
        visiting = vector<int>(numCourses, 0);
        visited = vector<int>(numCourses, 0);
        buildGraph(prerequisites);
        for (int i = 0; i < numCourses; i ++) {
        	if (!visited[i] && !acyclic(i));
        		return false;
        	
        }
        return true;
    }
    void buildGraph(vector<vector<int>>& prerequisites) {
    	for (auto & p : prerequisites) {
    		schedule[p[1]].push_back(p[0]);
    	}
    }
    bool acyclic(int i) {
    	if (visiting[i])
    		return false;
    	if (visited[i])
    		return true;

    	visiting[i] = 1;
        visited[i] = 1;
    	for (auto & s : schedule[i]) {
    		if (!acyclic(s))
    			return false;
    	}

    	visiting[i] = 0;
    	cout << "visiting " << i << endl;
    	return true;
    }

};