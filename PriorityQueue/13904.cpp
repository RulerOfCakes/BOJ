#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T, N, M;
    cin >> N;
    priority_queue<int, vector<int>, greater<int>> ansq;
    vector<vector<int>> v(1002, vector<int>());
    for (int i = 0; i < N; i++)
    {
        int d, w;
        cin >> d >> w;
        v[d].push_back(w);
    }
    for (int i = 1; i <= 1000; i++)
    {
        if (!v[i].empty())
        {
            sort(v[i].begin(), v[i].end(), greater<int>());
            int vidx = 0;
            vector<int> nv;
            while (ansq.size() + nv.size() < i && vidx < v[i].size())
            {
                nv.push_back(v[i][vidx++]);
            }
            while (ansq.size() + nv.size() == i && !ansq.empty() && vidx < v[i].size() && v[i][vidx] > ansq.top())
            {
                ansq.pop();
                nv.push_back(v[i][vidx++]);
            }
            for (int nx : nv)
            {
                ansq.push(nx);
            }
        }
    }

    int ans = 0;
    while (!ansq.empty())
    {
        ans += ansq.top();
        ansq.pop();
    }
    cout << ans;
}