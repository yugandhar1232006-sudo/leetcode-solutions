class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        vector<pair<int,int>> litter;
        int sr = 0, sc = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();
        if (k == 0) return 0;

        int total = 1 << k;

        vector<vector<vector<int>>> dist(
            m, vector<vector<int>>(n, vector<int>(total, -1))
        );

        queue<array<int,4>> q;

        dist[sr][sc][0] = energy;
        q.push({sr, sc, 0, energy});

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (mask == total - 1)
                    return moves;

                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if (classroom[nr][nc] == 'R')
                        ne = energy;

                    for (int i = 0; i < k; i++) {
                        if (litter[i].first == nr &&
                            litter[i].second == nc) {
                            nmask |= (1 << i);
                        }
                    }

                    if (dist[nr][nc][nmask] >= ne)
                        continue;

                    dist[nr][nc][nmask] = ne;
                    q.push({nr, nc, nmask, ne});
                }
            }

            moves++;
        }

        return -1;
    }
};