class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available;

        using T = tuple<long long, int, int>;
        priority_queue<T, vector<T>, greater<T>> busy;

        int n = servers.size();
        int m = tasks.size();

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        for (int i = 0; i < m; i++) {
            long long time = i;

            while (!busy.empty() && get<0>(busy.top()) <= time) {
                auto [endTime, weight, index] = busy.top();
                busy.pop();
                available.push({weight, index});
            }

            if (available.empty()) {
                time = get<0>(busy.top());

                while (!busy.empty() && get<0>(busy.top()) <= time) {
                    auto [endTime, weight, index] = busy.top();
                    busy.pop();
                    available.push({weight, index});
                }
            }

            auto [weight, index] = available.top();
            available.pop();

            ans[i] = index;
            busy.push({time + tasks[i], weight, index});
        }

        return ans;
    }
};