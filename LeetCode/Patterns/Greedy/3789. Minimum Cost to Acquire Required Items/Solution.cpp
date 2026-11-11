class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long ans = LLONG_MAX;

        vector<long long> candidates = {0, min(need1, need2), max(need1, need2)};

        for (long long both : candidates) {
            long long cost = both * costBoth
                           + max(0LL, need1 - both) * cost1
                           + max(0LL, need2 - both) * cost2;

            ans = min(ans, cost);
        }

        return ans;
    }
};