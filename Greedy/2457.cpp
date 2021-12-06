#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;

int N;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    vector<pi> v;
    int start = 3 * 31 + 1, end = 11 * 31 + 30;
    for (int i = 0; i < N; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a * 31 + b < start)
        {
            if (c * 31 + d <= start)
            {
                continue;
            }
            a = 3;
            b = 1;
        }
        v.push_back({a * 31 + b, c * 31 + d});
    }
    sort(v.begin(), v.end());
    // for(auto p : v){
    //     cout << p.first << ' ' << p.second << '\n';
    // }
    // cout << endl;
    int cx = start, cnt = 0, tx = 0, idx = 0;
    while (cx <= end && idx < v.size())
    {
        pi p = v[idx++];
        //cout << p.first << ' ' << p.second << ' ' << cx << ' ' << tx << endl;
        if (p.first > cx)
        {
            if (p.first > tx)
                break;
            cx = tx;
            cnt++;
            tx = p.second;
        }
        else
        {
            tx = max(tx, p.second);
        }
    }
    if (cx <= end)
    {
        if (tx > cx)
        {
            cx = tx;
            cnt++;
        }
    }
    if (cx <= end)
    {
        cout << 0;
    }
    else
    {
        cout << cnt;
    }
}