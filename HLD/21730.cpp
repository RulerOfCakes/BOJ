#include <bits/stdc++.h>
#define MAXN 200020
using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int INF = 1e9+7;

int N, M, Q;
namespace seg{
    //segment tree - with lazy update
    int tree[1<<19];
    int lazy[1<<19];
    int sz = 1<<18;

    void init(){
        for(int i = 1; i < (1<<19); i++){
            tree[i]=0;
            lazy[i]=0;
        }
    }

    void update_lazy(int node, int s, int e){
        if(!lazy[node])return;
        if(s==e){
            if(s%2)
                tree[node]+=lazy[node];
            else 
                tree[node]-=lazy[node];
        }
        else{
            lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node]=0;
    }

    void update(int node, int s, int e, int l, int r, int v){
        update_lazy(node,s,e);
        if(r<s||e<l)return;
        if(l<=s&&e<=r){
            lazy[node]=v;
            update_lazy(node,s,e);
            return;
        }
        int mid=s+e>>1;
        update(node*2,s,mid,l,r,v);
        update(node*2+1,mid+1,e,l,r,v);
        tree[node]=tree[node*2]+tree[node*2+1];
    }

    int query(int node, int s, int e, int l, int r){
        update_lazy(node,s,e);
        if(r<s||e<l)return 0;
        if(l<=s&&e<=r)return tree[node];
        int mid = s+e>>1;
        return query(node*2,s,mid,l,r)+query(node*2+1,mid+1,e,l,r);
    }
}


bool chk[MAXN];

int sz[MAXN],depth[MAXN],par[MAXN],top[MAXN],in[MAXN],out[MAXN];
/*
sz : size of subtree with i as root
depth : depth of i
par : parent of i
top : index of the top vertex of the chain i belongs to
in, out : dfs ordering(euler tour trick)
*/
vector<int> adj[MAXN],tadj[MAXN];
//directed graph
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

void update(int a, int b, int val){
    while(top[a]!=top[b]){
        //different chain
        if(depth[top[a]]<depth[top[b]])swap(a,b);
        int st=top[a];
        
        seg::update(1,1,seg::sz,in[st],in[a],val);
        a=par[st];
    }
    if(depth[a]>depth[b])swap(a,b);
    
    seg::update(1,1,seg::sz,in[a],in[b],val);
}

int query(int a, int b){
    int ret = 0;
    while(top[a] != top[b]){
        if(depth[top[a]] < depth[top[b]]) swap(a, b);
        int st = top[a];
        ret += seg::query(1,1,seg::sz,in[st], in[a]);
        a = par[st];
    }
    if(depth[a] > depth[b]) swap(a, b);
    ret += seg::query(1,1,seg::sz,in[a], in[b]);
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M >> Q;
    for(int i = 1; i <= N-1; i++){
        int a,b;
        cin >> a >> b;
        int c = N+i;
        tadj[a].push_back(c);
        tadj[c].push_back(a);
        tadj[c].push_back(b);
        tadj[b].push_back(c);
    }
    top[1]=1;
    dfs();
    dfs1();
    dfs2();
    seg::init();
    vector<pi> watchers(M+1);
    for(int i = 0; i < M; i++){
        int s,e;
        cin>>s>>e;
        watchers[i+1]={s,e};
    }
    for(int i = 0; i < Q; i++){
        int a,b,c;
        cin>>a>>b;
        if(a==1){
            cin>>c;
            update(b,c,1);
        }
        else{
            auto [s,e] = watchers[b];
            cout << query(s,e) << '\n';
        }
    }
    
}