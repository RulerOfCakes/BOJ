#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;
const int INF = 1e9+7;

class segtree
{
public:
    vector<int> tree;

    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, INF);
    }
    void update(int node, int x)
    {
        int idx = size + node - 1;
        tree[idx]=x;
        idx/=2;
        while (idx)
        {
            tree[idx] = min(tree[idx*2],tree[idx*2+1]);
           
            idx /= 2;
        }
    }
    
    int query(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        if (nEnd < rStart || nStart > rEnd)
            return INF;
        if (rStart <= nStart && rEnd >= nEnd)
            return tree[node];
        int mid = (nStart + nEnd) / 2;
        return min(query(node * 2, nStart, mid, rStart, rEnd), query(node * 2 + 1, mid + 1, nEnd, rStart, rEnd));
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    segtree seg(N+1);
    for(int i = 0; i < N; i++){
        int a;cin>>a;
        seg.update(i+1,a);
    }
    for(int i = 0; i < M; i++){
        int a,b;
        cin >> a >> b;
        cout << seg.query(1,1,seg.size,a,b) << '\n';
    }
}