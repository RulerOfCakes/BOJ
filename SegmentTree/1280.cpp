#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;
const int MOD = 1e9 + 7;

class segtree
{
public:
    vector<long long> tree;
    vector<int> cnt;

    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, 0);
        cnt.resize(size * 2, 0);
    }
    void update(int node, long long x)
    {
        int idx = size + node - 1;
        long long diff = x;
        while (idx)
        {
            tree[idx] += diff;
           
            idx /= 2;
        }
        idx = size + node - 1;
        while (idx)
        {
            cnt[idx]++;
            idx /= 2;
        }
    }
    // int query(int node, int nStart, int nEnd, int rStart, int rEnd)
    // {
    //     if (nEnd < rStart || nStart > rEnd)
    //         return 1;
    //     if (rStart <= nStart && rEnd >= nEnd)
    //         return tree[node];
    //     int mid = (nStart + nEnd) / 2;
    //     return query(node * 2, nStart, mid, rStart, rEnd) * query(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    // }
    ll getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        if (nEnd < rStart || nStart > rEnd)
            return 0;
        if (rStart <= nStart && rEnd >= nEnd)
            return tree[node];
        int mid = (nStart + nEnd) / 2;
        return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    }
    int getcnt(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        if (nEnd < rStart || nStart > rEnd)
            return 0;
        if (rStart <= nStart && rEnd >= nEnd)
            return cnt[node];
        int mid = (nStart + nEnd) / 2;
        return getcnt(node * 2, nStart, mid, rStart, rEnd) + getcnt(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b;
    cin >> N;
    segtree seg(200002);
    ll ans = 1;
    for (int i = 0; i < N; i++)
    {
        cin >> a;
        a += 1;
        if(i==0){
            seg.update(a,a);
            continue;
        }
    ll temp = 0;
        ll lcnt = seg.getcnt(1, 1, seg.size, 1, a), rcnt = seg.getcnt(1, 1, seg.size, a, 200001);
        if (lcnt)
        {
            temp += lcnt * a - seg.getsum(1, 1, seg.size, 1, a);
            
        }
        if (rcnt)
        {
            temp+= seg.getsum(1, 1, seg.size, a, 200001) - a * rcnt;
            
        }
        ans *= temp%MOD;
        ans%=MOD;
        seg.update(a, a);
    }
    cout << ans;
}