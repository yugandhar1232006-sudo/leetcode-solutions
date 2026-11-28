class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int mx = 0;
        int minPrice = INT_MAX;

        vector<int> freq(n + 1, 0);

        for (auto& item : items) {
            freq[item[0]]++;
            mx = max(mx, item[0]);
            minPrice = min(minPrice, item[1]);
        }

        vector<int> gain(mx + 1, 0);

        for (int i = 1; i <= mx; i++) {
            for (int j = i; j <= mx; j += i) {
                gain[i] += freq[j];
            }
            gain[i]--;
        }

        sort(items.begin(), items.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        long long ans = 0;
        long long remaining = budget;

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            if (price >= 2LL * minPrice)
                break;

            if (gain[factor] <= 0)
                continue;

            long long take = min((long long)gain[factor],
                                 remaining / price);

            ans += 2 * take;
            remaining -= take * price;
        }

        ans += remaining / minPrice;

        return ans;
    }
};