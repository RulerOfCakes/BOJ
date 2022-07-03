#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class segtree
{
public:
    vector<long long> tree;
    int size;
    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, 0);
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
int N;
struct query
{
    bool type;
    ll a, b;
};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    vector<query> v;
    segtree seg(202020);
    map<ll, int> idxmp, exists;
    vector<ll> cv;
    while (N--)
    {
        int t;
        ll a, b = 0;
        cin >> t >> a;
        if (t == 1)
            cin >> b;
        v.push_back({t == 1 ? true : false, a, b});
        if (t == 1)
        {
            if (a == 0)
                continue;
            // exists[-b / a] = 1;
            if (!(b % a))
                cv.push_back(b / a);
            else
                cv.push_back(floorl((long double)b / a));
        }
        else
        {
            cv.push_back(-a);
        }
    }
    int rcnt = 0;
    int tcnt = 0;
    sort(cv.begin(), cv.end());
    cv.erase(unique(cv.begin(), cv.end()), cv.end());
    for (int i = 0; i < cv.size(); i++)
    {
        idxmp[cv[i]] = i + 2;
    }

    bool doomed = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].type)
        {
            if (v[i].a == 0)
            {
                if (v[i].b < 0)
                    rcnt++;
                else if (v[i].b == 0)
                {
                    doomed = 1;
                }
                continue;
            }

            tcnt++;
            int point;
            if (!(v[i].b % v[i].a))
            {
                exists[v[i].b / v[i].a] = 1;
                point = idxmp[v[i].b / v[i].a];
            }
            else
            {
                point = idxmp[floorl((long double)v[i].b / v[i].a)];
            }
            assert(point);
            seg.update(point, 1);
            if (v[i].a < 0)
            {
                rcnt++;
            }
        }
        else
        {
            if (doomed)
            {
                cout << "0\n";
                continue;
            }

            if (exists.count(-v[i].a))
            {
                cout << "0\n";
            }
            else
            {
                assert(idxmp[-v[i].a]);
                ll query = seg.getsum(1, 1, seg.size, 1, idxmp[-v[i].a] - 1);
                // cout << query << ' ' << "SEE" << ' ';
                if ((rcnt) % 2)
                {
                    cout << ((query % 2) ? "+" : "-") << '\n';
                }
                else
                {
                    cout << ((query % 2) ? "-" : "+") << '\n';
                }
            }
        }
    }
}