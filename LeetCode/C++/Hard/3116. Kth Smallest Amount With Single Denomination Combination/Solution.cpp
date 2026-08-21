class Solution {
public:
    long long gcd(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    long long lcm(long long a, long long b) {
        return a / gcd(a, b) * b;
    }

    long long count(long long x, vector<int>& coins) {
        long long res = 0;
        int m = coins.size();

        for (int mask = 1; mask < (1 << m); mask++) {
            long long L = 1;
            bool ok = true;
            int bits = 0;

            for (int i = 0; i < m; i++) {
                if (mask & (1 << i)) {
                    bits++;
                    L = lcm(L, (long long)coins[i]);

                    if (L > x) {
                        ok = false;
                        break;
                    }
                }
            }

            if (!ok) continue;

            long long v = x / L;

            if (bits & 1)
                res += v;
            else
                res -= v;
        }

        return res;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (count(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};