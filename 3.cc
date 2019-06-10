#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <tuple>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <ctime>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <numeric>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;


string help(string s)
{
    int n = s.size();
    int index0 = 0;
    int index1 = 0;
    int index2 = n - 1;
    int times = 0;
    string s1;
    string s2;
    string s3;
    string ret;

    while (s[index1] != '%' && index1 < index2) index1++;
    while (s[index2] != '#' && index2 > index1) index2 ++;
    
    if (index1 < index2) s2 = s.substr(index1+1, index2-index1-1);
    else return s;

    s2 = help(s2);

    if (index2 < n-1)
        s3 = s.substr(index2+1, n-index2-1);
    

    index0 = index1-1;
    while (index0 >= 0 && (s[index0] > '0' && s[index0] < '9'))
        index0--;

    index0++;

    times = (index1 - index0 == 0? 0: stoi(s.substr(index0, index1-index0)));
    
    s1 = s.substr(0, index0);

    ret += s1;

    for (int i = 0; i < times; ++i) {
        ret += s2;
    }

    ret += s3;

    return ret;
}

int main(int argc, const char * argv[]) {
    
    string s; 
    cin >> s;
    string ret;

    int num = 0;
    int lastPoint = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '%') num++;
        else if (s[i] == '#') {
            num--;
            if (num == 0) {
                ret += help(s.substr(lastPoint, i-lastPoint+1));
                lastPoint = i + 1;
            }
        }
    }
    // string ret = help(s);

    cout << ret << endl;

    return 0;
}