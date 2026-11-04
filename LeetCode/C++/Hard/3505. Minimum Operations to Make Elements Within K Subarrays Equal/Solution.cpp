class Solution {
public:
    struct Fenwick {
        int n;
        vector<long long> bit;

        Fenwick(int n) {
            this->n = n;
            bit.assign(n + 1, 0);
        }

        void add(int i, long long val) {
            for (i++; i <= n; i += i & -i)
                bit[i] += val;
        }

        long long sum(int i) {
            long long res = 0;
            for (; i > 0; i -= i & -i)
                res += bit[i];
            return res;
        }

        int kth(int k) {
            int idx = 0;
            int mask = 1;

            while ((mask << 1) <= n)
                mask <<= 1;

            for (; mask; mask >>= 1) {
                int next = idx + mask;

                if (next <= n && bit[next] < k) {
                    idx = next;
                    k -= bit[next];
                }
            }

            return idx;
        }
    };

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();

        Fenwick cnt(m), sum(m);

        auto update = [&](int v, int delta) {
            int id = lower_bound(vals.begin(), vals.end(), v) - vals.begin();
            cnt.add(id, delta);
            sum.add(id, 1LL * v * delta);
        };

        auto getCost = [&]() -> long long {
            int mid = cnt.kth((x + 1) / 2);
            long long median = vals[mid];

            long long leftCount = cnt.sum(mid + 1);
            long long leftSum = sum.sum(mid + 1);

            long long totalSum = sum.sum(m);

            return median * leftCount - leftSum
                 + (totalSum - leftSum)
                 - median * (x - leftCount);
        };

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++)
            update(nums[i], 1);

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            update(nums[i - x], -1);
            update(nums[i], 1);
            cost[i - x + 1] = getCost();
        }

        const long long INF = LLONG_MAX / 4;

        vector<long long> prev(n + 1, 0), curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x) {
                    int start = i - x;

                    if (prev[start] != INF) {
                        curr[i] = min(curr[i],
                                      prev[start] + cost[start]);
                    }
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};