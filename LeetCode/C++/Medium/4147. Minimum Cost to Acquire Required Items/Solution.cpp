class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long a = need1;
        long long b = need2;

        long long ans1 = a * cost1 + b * cost2;
        long long ans2 = min(a, b) * costBoth
                       + abs(a - b) * min(cost1, cost2 + cost1);

        long long ans3 = max(a, b) * costBoth;

        return min({ans1, ans2, ans3});
    }
};