class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();

        const int NEG = -1e9;

        vector<vector<vector<int>>> dp(
            m, vector<vector<int>>(n, vector<int>(3, NEG))
        );

        dp[0][0][0] = coins[0][0];

        if (coins[0][0] < 0) {
            dp[0][0][1] = 0;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int used = 0; used <= 2; used++) {

                    int value = coins[i][j];

                    if (i > 0 && dp[i - 1][j][used] != NEG) {
                        dp[i][j][used] = max(
                            dp[i][j][used],
                            dp[i - 1][j][used] + value
                        );
                    }

                    if (j > 0 && dp[i][j - 1][used] != NEG) {
                        dp[i][j][used] = max(
                            dp[i][j][used],
                            dp[i][j - 1][used] + value
                        );
                    }

                    if (coins[i][j] < 0 && used > 0) {

                        if (i > 0 && dp[i - 1][j][used - 1] != NEG) {
                            dp[i][j][used] = max(
                                dp[i][j][used],
                                dp[i - 1][j][used - 1]
                            );
                        }

                        if (j > 0 && dp[i][j - 1][used - 1] != NEG) {
                            dp[i][j][used] = max(
                                dp[i][j][used],
                                dp[i][j - 1][used - 1]
                            );
                        }
                    }
                }
            }
        }

        return max({
            dp[m - 1][n - 1][0],
            dp[m - 1][n - 1][1],
            dp[m - 1][n - 1][2]
        });
    }
};