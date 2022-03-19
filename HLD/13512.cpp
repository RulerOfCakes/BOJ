#include <bits/stdc++.h>
#define MAXN 100002
using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int INF = 1e9+7;

int N, M;
namespace seg{
    //segment tree - min/max trees with lazy update
    pi mintree[1<<18];

    void init(){
        for(int i = 1; i < (1<<18); i++){
            mintree[i]={INF,-1};
        }
    }
    void update(int pos, pi x){
        int idx=pos+(1<<17)-1;
        mintree[idx]=x;
        idx/=2;
        while(idx){
            mintree[idx]=min(mintree[idx<<1],mintree[idx<<1|1]);
            idx/=2;
        }
    }

    pi query_min(int node, int s, int e, int l, int r){
        if(r<s||e<l)return {INF,-1};
        if(l<=s&&e<=r)return mintree[node];
        int mid = s+e>>1;
        return min(query_min(node*2,s,mid,l,r),query_min(node*2+1,mid+1,e,l,r));
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


bool colors[MAXN];
void update(int x){
    if(colors[x]){
        seg::update(in[x],{INF,-1});
    } else {
        seg::update(in[x],{depth[x],x});
    }
    colors[x]=!colors[x];
}

pi query(int a, int b){
    pi ret={INF,-1};
    while(top[a]!=top[b]){
        if(depth[top[a]]<depth[top[b]])swap(a,b);
        int st=top[a];
        ret=min(ret,seg::query_min(1,1,1<<17,in[st],in[a]));
        a=par[st];
    }
    if(depth[a]>depth[b])swap(a,b);
    ret=min(ret,seg::query_min(1,1,1<<17,in[a],in[b]));
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 0; i < N-1; i++){
        int a,b;
        cin >> a >> b;
        tadj[a].push_back(b);
        tadj[b].push_back(a);
    }
    cin >> M;
    top[1]=1;
    dfs();
    dfs1();
    dfs2();
    seg::init();
    for(int i = 0; i < M; i++){
        int a,b;
        cin >>a >> b;
        if(a==1){
            update(b);
        }
        else{
            cout << query(1,b).second << '\n';
        }
    }
    
    
}