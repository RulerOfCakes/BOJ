#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<ll, ll>;

int N, M;
const int INF = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll a, b;
    cin >> N >> M;
    vector<pi> lines;
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b;
        if (b < a)
        {
            swap(a, b);
            lines.push_back(make_pair(a, b));
        }
    }
    sort(lines.begin(), lines.end());

    ll ans = 0, l = -INF, r = -INF;
    for (int i = 0; i < lines.size(); i++)
    {
        if (r < lines[i].first)
        {
            ans += r - l;
            l = lines[i].first;
            r = lines[i].second;
        }
        else
        {
            r = max(r, lines[i].second);
        }
    }
    ans += r - l;
    cout << M + ans * 2;
}