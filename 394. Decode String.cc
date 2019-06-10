class Solution {
int index = 0;
public:

    string decodeString(string s) {
        int digit = 1;
        int previousIsDigit = false;
        string finalstr = "";
        string localstr = "";

        for (; index < s.size(); index++) {
            if (s[index] == ']')
                return finalstr;
            if (isdigit(s[index])) {
                if (!previousIsDigit)
                    digit = s[index] - '0';
                else
                    digit = digit * 10 + (s[index] - '0');
                previousIsDigit = true;
            }
            else if ((s[index] == '[')) {
                previousIsDigit = false;
                index ++;
                string str = decodeString(s);
                for (int j = 0; j < digit; j++) {
                    finalstr += str;
                }
                digit = 1;
                while (index < s.size() && s[index] != ']') 
                index++;       
            }
            else {
                previousIsDigit = false;
                while(isalpha(s[index]) && index < s.size()) {
                    localstr += s[index];
                    index++;
                }
                index--;
                for (int j = 0; j < digit; j++) {
                    finalstr += localstr;
                }
                digit = 1;
                localstr = "";
            }

            }
        return finalstr; 
    }
};