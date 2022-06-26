#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using ppl = pair<pl, pl>;
int N, M, K;
const ll INF = 1e18;

class segtree
{
public:
    vector<long long> tree;
    vector<ll> mtree;
    vector<ll> ltree;
    vector<ll> rtree;
    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, 0);
        mtree.resize(size * 2, -INF);
        ltree.resize(size * 2, -INF);
        rtree.resize(size * 2, -INF);
    }
    void update(int node, long long x)
    {
        int idx = size + node - 1;
        long long diff = x - tree[idx];
        tree[idx] = diff;
        mtree[idx] = diff;
        ltree[idx] = diff;
        rtree[idx] = diff;
        idx /= 2;
        while (idx)
        {
            tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
            mtree[idx] = max({mtree[idx << 1], mtree[idx << 1 | 1], rtree[idx << 1] + ltree[idx << 1 | 1]});
            ltree[idx] = max({ltree[idx << 1], tree[idx << 1] + ltree[idx << 1 | 1]});
            rtree[idx] = max({rtree[idx << 1 | 1], tree[idx << 1 | 1] + rtree[idx << 1]});
            idx >>= 1;
        }
    }
    ppl query(int n, int s, int e, int l, int r)
    {
        if (e < l || r < s)
            return {{0, -INF}, {-INF, -INF}};
        if (l <= s && e <= r)
            return {{tree[n], mtree[n]}, {ltree[n], rtree[n]}};
        int m = s + e >> 1;
        auto [ls, ld] = query(n << 1, s, m, l, r);
        auto [rs, rd] = query(n << 1 | 1, m + 1, e, l, r);
        return {{ls.first + rs.first, max({ls.second, rs.second, ld.second + rd.first})},
                {max(ld.first, ls.first + rd.first), max(rd.second, rs.first + ld.second)}};
    }
    long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        if (nEnd < rStart || nStart > rEnd)
            return 0;
        if (rStart <= nStart && rEnd >= nEnd)
            return tree[node];
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
    segtree seg(N);
    for (int n = 0; n < N; n++)
    {
        cin >> a;
        seg.update(n + 1, a);
    }
    cin >> M;
    while (M--)
    {
        cin >> a >> b;
        ppl ans = seg.query(1, 1, seg.size, a, b);
        cout << max({ans.first.first, ans.first.second, ans.second.first, ans.second.second}) << '\n';
    }
}