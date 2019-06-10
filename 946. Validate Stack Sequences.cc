class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> mystack;
        int i = 0;

        for (auto &s : pushed) {
        	mystack.push(s);

        	while (!mystack.empty() && mystack.top() == popped[i]) {
        		i ++;
        		
        		mystack.pop();
        	}

        }
        if (mystack.empty() && i == popped.size()){
        	return true;
        }
        return false;
    }
};


class Solution {
public:
  bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int i = 0;
        for (int x : pushed) {
            s.push(x);
            while (s.size() && s.top() == popped[i]) {
                s.pop();
                i++;
            }
        }
        return i == popped.size();
    }
};