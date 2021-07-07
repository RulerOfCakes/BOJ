#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ppi = pair<pi, pi>;

int T, N;
const int INF = 1e4 + 4;
//const int MOD = 1e9 + 7;

class segtree
{
public:
    // vector<long long> tree;
    vector<long long> cnt; // count of lines
    vector<long long> sum; // sum of squares
    //vector<long long> lazy; // lazy propagataion
    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        //tree.resize(size * 2, 0);
        //lazy.resize(size * 2);
        cnt.resize(size * 2);
        sum.resize(size * 2);
    }
    // void update(int node, long long x)
    // {
    //     int idx = size + node - 1;
    //     long long diff = x - tree[idx];
    //     while (idx)
    //     {
    //         tree[idx] += diff;
    //         idx /= 2;
    //     }
    // }

    void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff)
    {

        if (nEnd < rStart || nStart > rEnd)
            return;
        if (nStart >= rStart && nEnd <= rEnd)
        {
            cnt[node] += diff;
        }
        else
        {
            int mid = (nStart + nEnd) / 2;
            update_range(node * 2, nStart, mid, rStart, rEnd, diff);
            update_range(node * 2 + 1, mid + 1, nEnd, rStart, rEnd, diff);
        }

        if (cnt[node] > 0)
        {
            sum[node] = nEnd - nStart + 1;
        }
        else if (nStart != nEnd)
        {
            sum[node] = sum[node * 2] + sum[node * 2 + 1];
        }
        else
        {
            sum[node] = 0;
        }
    }
    long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    {

        if (nEnd < rStart || nStart > rEnd)
            return 0;
        if (rStart <= nStart && rEnd >= nEnd)
            return sum[node];
        int mid = (nStart + nEnd) / 2;
        return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c, d;

    cin >> N;
    segtree seg(2 * INF);
    segtree seg2(2 * INF);
    vector<ppi> v;
    vector<ppi> v2;

    //v layout
    //{{starting point, start/finish}, {ybottom, ytop}}
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b >> c >> d;
        int ta=a,tb=b,tc=c,td=d;
        a=min(ta,tc);
        b=min(tb,td);
        c=max(ta,tc);
        d=max(tb,td);
        a += INF;
        b += INF;
        c += INF;
        d += INF;
        v.push_back({{a, 0}, {b, d}});
        v.push_back({{c, 1}, {b, d}});
        v2.push_back({{b, 0}, {a, c}});
        v2.push_back({{d, 1}, {a, c}});
    }
    sort(v.begin(), v.end());
    sort(v2.begin(), v2.end());

    ll ans = 0;
    ll prev = -1;
    for (int i = 0; i < v.size(); i++)
    {

        int cx = v[i].first.first, param = v[i].first.second,
            sy = v[i].second.first, ey = v[i].second.second;
        if (param)
            seg.update_range(1, 1, seg.size, sy, ey - 1, -1);
        else
            seg.update_range(1, 1, seg.size, sy, ey - 1, 1);
        ll res = seg.sum[1];
        if (res < prev)
            ans += ((prev - res) * 2);
        prev = res;
    }
    prev = -1;
    for (int i = 0; i < v2.size(); i++)
    {
        int cy = v2[i].first.first, param = v2[i].first.second,
            sx = v2[i].second.first, ex = v2[i].second.second;
        if (param)
            seg2.update_range(1, 1, seg2.size, sx, ex- 1, -1);
        else
            seg2.update_range(1, 1, seg2.size, sx, ex - 1, 1);
        ll res = seg2.sum[1];
        if (res < prev)
            ans += ((prev - res) * 2);
        prev = res;
    }
    cout << ans << '\n';
}