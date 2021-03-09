#include <bits/stdc++.h>

using namespace std;

using pi = pair<int, int>;

int N, T;
vector<pi> v;
set<pi> s;
int dist(pi p1, pi p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while (T--)
    {
        cin >> N;
        v.clear();
        s.clear();
        for (int i = 0; i < N; i++)
        {
            pi temp;
            cin >> temp.first >> temp.second;
            v.push_back(temp);
            s.insert(temp);
        }
        sort(v.begin(), v.end());
        int ans = 0;
        for (int i = 0; i < N - 1; i++)
        {
            pi cur1 = v[i];
            for (int j = i + 1; j < N; j++)
            {
                pi cur2 = v[j];
                int dx = cur2.first - cur1.first, dy = cur2.second - cur1.second;
                if (s.find({cur2.first - dy, cur2.second + dx}) != s.end() &&
                    s.find({cur1.first - dy, cur1.second + dx}) != s.end())
                {
                    ans = max(ans, dist(cur1, cur2));
                }
            }
        }
        cout << ans << '\n';
    }
}