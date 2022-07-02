#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<ll, ll>;

int ccw(pi p1, pi p2, pi p3)
{
    ll sol = (p1.first * p2.second + p2.first * p3.second + p3.first * p1.second) - (p1.second * p2.first + p2.second * p3.first + p3.second * p1.first);
    if (sol < 0)
        return -1;
    else if (sol == 0)
        return 0;
    else
        return 1;
}
int intersection(pi p1, pi p2, pi p3, pi p4)
{
    int first = ccw(p1, p2, p3), second = ccw(p1, p2, p4);
    int third = ccw(p3, p4, p1), fourth = ccw(p3, p4, p2);
    int check1 = first * second, check2 = third * fourth;
    if (check1 == 0 && check2 == 0)
    {
        return min(p3, p4) <= max(p1, p2) && min(p1, p2) <= max(p3, p4);
    }
    return check1 <= 0 && check2 <= 0;
}

struct swing
{
    pi start, end;
    ll w;
};
int N;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    vector<swing> v;
    for (int i = 0; i < N; i++)
    {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        v.push_back({{a, b}, {c, d}, e});
    }
    vector<set<int>> cntv(N, set<int>());
    vector<int> cv;
    for (int i = 0; i < N; i++)
    {
        cv.push_back(i);
        for (int j = i + 1; j < N; j++)
        {
            if (intersection(v[i].start, v[i].end, v[j].start, v[j].end))
            {
                cntv[i].insert(j);
                cntv[j].insert(i);
            }
        }
    }
    ll ans = 0;
    set<int> cs(cv.begin(), cv.end());
    for (int t = 0; t < N; t++)
    {
        int minidx = 0;
        ll minval = LLONG_MAX;
        for (int i : cs)
        {
            if (v[i].w < minval)
            {
                minval = v[i].w;
                minidx = i;
            }
        }
        ans += (cntv[minidx].size() + 1) * minval;
        cs.erase(minidx);
        for (int i : cs)
        {
            if (cntv[i].count(minidx))
            {
                cntv[i].erase(minidx);
            }
        }
    }
    cout << ans;
}