
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int pig = 0;
        int base = ceil(minutesToTest / minutesToDie) + 1;
        while (pow(base, pig) < buckets) pig ++;
        return pig;
    }
};