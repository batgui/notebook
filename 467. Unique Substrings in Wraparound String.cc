class Solution {
public:
    int findSubstringInWraproundString(string p) {
    	int globalCnt = 0;
    	int localCnt = 1;
        for (int i = 1; i < p.size(); i++) {
        	if ((p[i] + 26 - p[i - 1]) % 26 == 1) {
        		localCnt ++;
        	}
        	else {
        		globalCnt += localCnt * (1 + localCnt) / 2;
        		localCnt = 1;
        	}
        	
        }
        if (localCnt != 1)
        	globalCnt += localCnt * (1 + localCnt) / 2;
        return globalCnt;
    }
};