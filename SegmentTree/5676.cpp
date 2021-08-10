#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;

class segtree
{
public:
    vector<int> tree;

    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, 0);
    }
    void update(int node, int x)
    {
        int idx = size + node - 1;
        tree[idx] = x;
        idx /= 2;
        while (idx)
        {
            tree[idx] = tree[idx * 2] * tree[idx * 2 + 1];
            idx /= 2;
        }
    }

    int query(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        if (nEnd < rStart || nStart > rEnd)
            return 1;
        if (rStart <= nStart && rEnd >= nEnd)
            return tree[node];
        int mid = (nStart + nEnd) / 2;
        return query(node * 2, nStart, mid, rStart, rEnd) * query(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b;
    while (cin >> N >> K)
    {
        segtree seg(N);
        ll ans = 0;

        for (int n = 0; n < N; n++)
        {
            cin >> a;
            if (a > 0)
                a = 1;
            else if (a < 0)
                a = -1;
            seg.update(n + 1, a);
        }
        for (int i = 0; i < K; i++)
        {
            char c;
            cin >> c >> a >> b;
            if (c == 'C')
            {
                if (b > 0)
                    b = 1;
                else if (b < 0)
                    b = -1;
                seg.update(a, b);
            }
            else
            {
                int res = seg.query(1, 1, seg.size, a, b);
                if (res < 0)
                {
                    cout << '-';
                }
                else if (res > 0)
                {
                    cout << '+';
                }
                else
                    cout << 0;
            }
        }
        cout << '\n';
    }
}