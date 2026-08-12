class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        set<int, greater<int>> st;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                st.insert(grid[i][j]);

                for (int k = 1; i + 2 * k < m && j - k >= 0 && j + k < n; k++) {
                    int sum = 0;

                    for (int t = 0; t < k; t++)
                        sum += grid[i + t][j - t];

                    for (int t = 0; t < k; t++)
                        sum += grid[i + k + t][j - k + t];

                    for (int t = 0; t < k; t++)
                        sum += grid[i + 2 * k - t][j + t];

                    for (int t = 0; t < k; t++)
                        sum += grid[i + k - t][j + k - t];

                    st.insert(sum);

                    if (st.size() > 3)
                        st.erase(prev(st.end()));
                }
            }
        }

        vector<int> ans;

        for (int x : st) {
            ans.push_back(x);
            if (ans.size() == 3)
                break;
        }

        return ans;
    }
};