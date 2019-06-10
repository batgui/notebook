class Solution {
int i;
public:
    string countOfAtoms(string formula) {
    	string ans;
    	map<string, int> res = countAtoms(formula);
    	for (auto &s : res) {
    		ans += s.first;
    		if (s.second > 1 ) 
    			ans += to_string(s.second);
    	}
    	return ans;

    }
    map<string, int> countAtoms(string formula) {
    	map<string, int> count;
    	while (i < formula.size()) {
    		if (formula[i] == '(') {
    			i++;

    			auto insideres = countAtoms(formula);
    			auto digits = countDigit(formula);
    			for (auto &s : insideres) {
    				count[s.first] += s.second * digits;
    			}


    		}
    		else if (formula[i] == ')') {

    			return count;
    		}

    			string str = countAlpha(formula);
    			auto digits = countDigit(formula);
    			count[str] += digits;
    		}
    	}
    	return count;
    }
    int countDigit(string formula) {
    	string digits = "";
    	while (isdigit(formula[i]) && i < formula.size()) {
    		digits += formula[i];
    		i ++;
    	}
    	return digits == "" ? 1 : stoi(digits);
    }
    string countAlpha(string formula) {
    	string atom = "";
    	while (i < formula.size() && (atom == "" || islower(formula[i]))) {
    		atom += formula[i];
    		i++;
    	}
    	return atom;
    }

};