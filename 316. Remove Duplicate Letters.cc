class Solution {
public:
    string removeDuplicateLetters(string s) {
		vector cnt(26, 0);
		for (auto &st : s) {
			cnt[st - 'a'] = 1;
		}
        int l = 0;
		string res = "";
		int distinctNum = accumulate(cnt.begin(), cnt.end(), 0);
		cout << "distinctNum " << distinctNum << endl;
		for (int j = 0; j < distinctNum; j ++) {
			
			for (int i = 0; i < 26; i ++) {
				int end = -1;
				for (int k = l; k < s.size(); k++) {
					
					if (((s[k] - 'a') == i) && (res.find(s[k]) == string::npos)) {
						end = k;
						cout << "end " << end << endl;
						break;
                    }
				}
				if (end == -1) continue;
				vector cnt2(26, 0);
				for (int o = end; o < s.size(); o++)
					cnt2[s[o] - 'a'] = 1;
				
				for (auto & st : res)
					cnt2[st - 'a'] = 1;
				int sizeOfcnt2 = accumulate(cnt2.begin(), cnt2.end(), 0);
				if (sizeOfcnt2  == distinctNum){

					res += s[end];
					l = end + 1;
					break;
					}


				

			}
			
		}
    return res;
    }
};