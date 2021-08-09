#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;

class msegtree
{
public:
    vector<vector<int>> tree;
    //vector<long long> cnt; // count of lines
    //vector<long long> sum; // sum of squares
    //vector<long long> lazy; // lazy propagataion
    int size;

    msegtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, vector<int>());
        //lazy.resize(size * 2);
        //cnt.resize(size * 2);
        //sum.resize(size * 2);
    }
    void update(int node, int x)
    {
        node |= size;
        tree[node].push_back(x);
    }
    //after inputting all leaf nodes
    void build()
    {
        // for(int i = 1; i <= N; i++){
        //     update(i, arr[i]);
        // }
        for (int i = size - 1; i; i--)
        {
            tree[i].resize(tree[i * 2].size() + tree[i * 2 + 1].size());
            merge(tree[i * 2].begin(), tree[i * 2].end(),
             tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(), tree[i].begin());
        }
    }

    int query(int l, int r, int k){
        l |= size, r|=size;
        int ret=0;
        while(l<=r){
            if(l&1)ret+=tree[l].end()-upper_bound(tree[l].begin(),tree[l].end(),k), l++;
            if(~r&1)ret+=tree[r].end()-upper_bound(tree[r].begin(),tree[r].end(),k),r--;
            l>>=1,r>>=1;
        }
        return ret;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    msegtree seg(N);
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        seg.update(i+1, a);
    }
    seg.build();
    cin >> M;
    int prevans=0;
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >>b >> c;
        int l = a^prevans, r = b^prevans, k = c^prevans;
        prevans=seg.query(l,r,k);
        cout << prevans << '\n';
    }
}