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
    // int query(int node, int nStart, int nEnd, int rStart, int rEnd)
    // {
    //     if (nEnd < rStart || nStart > rEnd)
    //         return 1;
    //     if (rStart <= nStart && rEnd >= nEnd)
    //         return tree[node];
    //     int mid = (nStart + nEnd) / 2;
    //     return query(node * 2, nStart, mid, rStart, rEnd) * query(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    // }
    // int getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    // {
    //     if (nEnd < rStart || nStart > rEnd)
    //         return 0;
    //     if (rStart <= nStart && rEnd >= nEnd)
    //         return tree[node];
    //     int mid = (nStart + nEnd) / 2;
    //     return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    // }
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
    cin >> N;
    segtree seg(N);
    vector<vector<int>> v(3,vector<int>(N,0));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < N; j++){
            int a;
            cin >> a;
            v[i][a-1]=j+1;
            
        }
    }
    vector<tuple<int,int,int>> inputs(N);
    for(int i = 0; i < N; i++){
        inputs[i]=make_tuple(v[0][i],v[1][i],v[2][i]);
    }
    int ans=0;
    sort(inputs.begin(),inputs.end());
    for(int i = 0;i < N; i++){
        int a,b,c;
        tie(a,b,c)=inputs[i];
        
        int res = seg.query(1,1,seg.size,1,b);
        if(res>c)ans++;
        seg.update(b,c);
    }   
    cout << ans;
}