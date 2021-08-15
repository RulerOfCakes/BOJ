#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;
const int INF = 1e9 + 7;

class segtree
{
public:
    vector<int> tree;

    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2);
    }
    void update(int node, int x)
    {
        int idx = size + node - 1;
        tree[idx] = x;
        idx /= 2;
        while (idx)
        {
            tree[idx] = tree[idx * 2]+ tree[idx * 2 + 1];

            idx /= 2;
        }
    }
    // int getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    // {
    //     if (nEnd < rStart || nStart > rEnd)
    //         return 0;
    //     if (rStart <= nStart && rEnd >= nEnd)
    //         return tree[node];
    //     int mid = (nStart + nEnd) / 2;
    //     return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    // }
    int query(int node, int nStart, int nEnd, int val)
    {
        if(nStart==nEnd){
            
            update(nStart,0);
            return nStart-1;
        }
        int mid = (nStart + nEnd) / 2;
        if(tree[node*2]>=val){
            return query(node*2, nStart, mid,val);
        }
        else{
            return query(node*2+1, mid+1, nEnd,val-tree[node*2]);
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    segtree seg(N);
    vector<int> height(N);
    vector<int> rank(N);
    
    for (int i = 0; i < N; i++)
    {
        cin >> height[i];
    }
    sort(height.begin(),height.end());
    for(int i = 0; i < N; i++){
        seg.update(i+1,1);
    }
    vector<int> ans(N);
    for(int i = 0;i  < N; i++){
        cin >> rank[i];
    }
    for(int i = N-1; i>=  0; i--){
        int idx = seg.query(1,1,seg.size,rank[i]+1);
        ans[i]=height[idx];
    }
    for(int i = 0; i < N; i++){
        cout << ans[i] << '\n';
    }
}