class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        int first = -1;
        int prev = -1;
        int minDist = INT_MAX;

        ListNode* p = head;
        ListNode* q = head->next;
        int index = 1;

        while (q->next != nullptr) {
            if ((q->val > p->val && q->val > q->next->val) ||
                (q->val < p->val && q->val < q->next->val)) {

                if (first == -1) {
                    first = index;
                } else {
                    minDist = min(minDist, index - prev);
                    ans[1] = index - first;
                }

                prev = index;
            }

            p = q;
            q = q->next;
            index++;
        }

        if (minDist == INT_MAX)
            return {-1, -1};

        ans[0] = minDist;
        return ans;
    }
};