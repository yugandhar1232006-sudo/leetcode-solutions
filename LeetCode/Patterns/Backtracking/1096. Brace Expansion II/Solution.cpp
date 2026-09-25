class Solution {
public:
    set<string> parseExpr(string &s, int &i) {
        set<string> res = parseTerm(s, i);

        while (i < s.size() && s[i] == ',') {
            i++;
            set<string> next = parseTerm(s, i);
            res.insert(next.begin(), next.end());
        }

        return res;
    }

    set<string> parseTerm(string &s, int &i) {
        set<string> res = {""};

        while (i < s.size() && s[i] != '}' && s[i] != ',') {
            set<string> cur;

            if (s[i] == '{') {
                i++;
                cur = parseExpr(s, i);
                i++;
            } else {
                cur.insert(string(1, s[i]));
                i++;
            }

            set<string> temp;

            for (auto &a : res) {
                for (auto &b : cur) {
                    temp.insert(a + b);
                }
            }

            res = temp;
        }

        return res;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> res = parseExpr(expression, i);

        return vector<string>(res.begin(), res.end());
    }
};