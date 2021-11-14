#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class segtree
{
public:
    vector<ll> tree;
    vector<ll> lazy;
    int sz;
    segtree(int n){
        for(sz=1;sz<n;sz*=2);
        tree.resize(sz*2);
        lazy.resize(sz*2);
    }
    void update(int x, int v)
    {
        x |= sz;
        tree[x] += v;
        while (x >>= 1)
        {
            tree[x] = tree[x << 1] + tree[x << 1 | 1];
        }
    }

    int query(int l, int r)
    {
        l |= sz, r |= sz;
        int ret = 0;
        while (l <= r)
        {
            if (l & 1)
                ret += tree[l++];
            if (~r & 1)
                ret += tree[r--];
            l >>= 1, r >>= 1;
        }
        return ret;
    }
};

const int MAXN=1e6;
int sz[MAXN],depth[MAXN],par[MAXN],top[MAXN],in[MAXN],out[MAXN],chk[MAXN];
/*
sz : size of subtree with i as root
depth : depth of i
par : parent of i
top : index of the top vertex of the chain i belongs to
in, out : dfs ordering(euler tour trick)
*/
vector<int> adj[MAXN],tadj[MAXN];

//transforming to directed graph
void dfs(int v=1){
    chk[v]=1;
    for(auto i : tadj[v]){
        if(chk[i])continue;
        chk[i]=1;
        adj[v].push_back(i);
        dfs(i);
    }
}

//preprocessing sz, depth, par + heavy edge ordering
void dfs1(int v=1){
    sz[v]=1;
    for(auto &i : adj[v]){
        //if(i==par[v])continue;
        depth[i]=depth[v]+1;
        par[i]=v;
        dfs1(i);
        sz[v]+=sz[i];
        //move the heavy edge to the front
        if(sz[i]>sz[adj[v][0]])swap(i,adj[v][0]);
    }
}

//dfs ordering(euler tour trick) + top(chain) preprocessing
int pv;
void dfs2(int v=1){
    in[v]=++pv;
    for(auto i : adj[v]){
        //if(i==par[v])continue;
        top[i]=(i==adj[v][0]?top[v]:i);
        dfs2(i);
    }
    out[v]=pv;
}

int query(int a, int b, segtree& seg){
    int ret = 0;
    while(top[a]!=top[b]){
        if(depth[top[a]]<depth[top[b]])swap(a,b);
        int st=top[a];
        ret+=seg.query(in[st],in[a]);
        a=par[st];
    }
    if(depth[a]>depth[b])swap(a,b);
    ret+=seg.query(in[a],in[b]);
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    
    
    dfs();
    dfs1();
    dfs2();
}