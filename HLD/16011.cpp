#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int INF = 1e9+7;

int N, K;
namespace seg{
    //segment tree - min/max trees with lazy update
    int mintree[1<<18],maxtree[1<<18];
    int minlazy[1<<18],maxlazy[1<<18];

    void init(){
        for(int i = 1; i < (1<<18); i++){
            mintree[i]=INF;
            minlazy[i]=INF;
            maxtree[i]=-INF;
            maxlazy[i]=-INF;
        }
    }

    void lazy_min(int node, int s, int e){
        if(minlazy[node]==INF)return;
        mintree[node]=min(mintree[node],minlazy[node]);
        if(s!=e){
            minlazy[node*2]=min(minlazy[node],minlazy[node*2]);
            minlazy[node*2+1]=min(minlazy[node],minlazy[node*2+1]);
        }
        minlazy[node]=INF;
    }

    void lazy_max(int node, int s, int e){
        if(maxlazy[node]==-INF)return;
        maxtree[node]=max(maxtree[node],maxlazy[node]);
        if(s!=e){
            maxlazy[node*2]=max(maxlazy[node],maxlazy[node*2]);
            maxlazy[node*2+1]=max(maxlazy[node],maxlazy[node*2+1]);
        }
        maxlazy[node]=-INF;
    }

    void update_min(int node, int s, int e, int l, int r, int v){
        lazy_min(node,s,e);
        if(r<s||e<l)return;
        if(l<=s&&e<=r){
            mintree[node]=min(mintree[node],v);
            if(s!=e){
                minlazy[node*2]=min(minlazy[node*2],v);
                minlazy[node*2+1]=min(minlazy[node*2+1],v);
            }
            return;
        }
        int mid=s+e>>1;
        update_min(node*2,s,mid,l,r,v);
        update_min(node*2+1,mid+1,e,l,r,v);
        mintree[node]=min(mintree[node*2],mintree[node*2+1]);
    }

    void update_max(int node, int s, int e, int l, int r, int v){
        lazy_max(node,s,e);
        if(r<s||e<l)return;
        if(l<=s&&e<=r){
            maxtree[node]=max(maxtree[node],v);
            if(s!=e){
                maxlazy[node*2]=max(maxlazy[node*2],v);
                maxlazy[node*2+1]=max(maxlazy[node*2+1],v);
            }
            return;
        }
        int mid=s+e>>1;
        update_max(node*2,s,mid,l,r,v);
        update_max(node*2+1,mid+1,e,l,r,v);
        maxtree[node]=max(maxtree[node*2],maxtree[node*2+1]);
    }

    int query_min(int node, int s, int e, int l, int r){
        lazy_min(node,s,e);
        if(r<s||e<l)return INF;
        if(l<=s&&e<=r)return mintree[node];
        int mid = s+e>>1;
        return min(query_min(node*2,s,mid,l,r),query_min(node*2+1,mid+1,e,l,r));
    }

    int query_max(int node, int s, int e, int l, int r){
        lazy_max(node,s,e);
        if(r<s||e<l)return -INF;
        if(l<=s&&e<=r)return maxtree[node];
        int mid = s+e>>1;
        return max(query_max(node*2,s,mid,l,r),query_max(node*2+1,mid+1,e,l,r));
    }
}

struct query{
    int s,e;
    int val;
    bool op;
};
vector<query> qry;

map<int,int> mp;
//min node, max node, edge reference count, final answer(weight)
int minv[MAXN],maxv[MAXN],cnt[MAXN],ans[MAXN];
//storing node references to query
vector<int>track[MAXN];
//node visit, query visit
bool vis[MAXN],chk[MAXN];

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

void update(int a, int b, bool op, int val){
    while(top[a]!=top[b]){
        //different chain
        if(depth[top[a]]<depth[top[b]])swap(a,b);
        int st=top[a];
        if(op)seg::update_max(1,1,N,in[st],in[a],val);
        else seg::update_min(1,1,N,in[st],in[a],val);
        a=par[st];
    }
    if(depth[a]>depth[b])swap(a,b);
    if(op)seg::update_max(1,1,N,in[a]+1,in[b],val);
    else seg::update_min(1,1,N,in[a]+1,in[b],val);
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
    cin >> K;
    top[1]=1;
    dfs();
    dfs1();
    dfs2();
    seg::init();
    for(int i = 0; i < K; i++){
        char op;
        int a,b,c;
        cin >> op >> a >> b >> c;
        if(op=='M'){
            update(a,b,0,c);
        }
        else{
            update(a,b,1,c);
        }
        qry.push_back({a,b,c,op=='M'});
    }
    
    memset(chk,0,sizeof(chk));
    //query numbering
    for(int i = 0; i < K; i++){
        mp[qry[i].val]=i;
    }
    for(int i = 2; i <= N; i++){
        minv[i]=seg::query_min(1,1,N,in[i],in[i]);
        maxv[i]=seg::query_max(1,1,N,in[i],in[i]);
        if(minv[i]!=INF){
            cnt[mp[minv[i]]]++;
            track[mp[minv[i]]].push_back(i);
        }
        if(maxv[i]!=-INF){
            cnt[mp[maxv[i]]]++;
            track[mp[maxv[i]]].push_back(i);
        }
    }
    //number of edge references, current query idx
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    for(int i = 0; i < K; i++){
        pq.push({cnt[mp[qry[i].val]],i});
    }
    //in the order of least references, update any relevant node in greedy fashion
    while(!pq.empty()){
        pi now = pq.top();
        pq.pop();
        if(now.first!=cnt[now.second])continue;
        vis[now.second]=1;
        //nodes that refer to this query
        for(int i : track[now.second]){
            if(chk[i])continue;
            chk[i]=1;
            ans[i]=qry[now.second].val;
            if(qry[now.second].op){
                if(maxv[i]!=-INF){
                    cnt[mp[maxv[i]]]--;
                    if(!vis[mp[maxv[i]]])pq.push({cnt[mp[maxv[i]]],mp[maxv[i]]});
                }
            }
            else{
                if(minv[i]!=INF){
                    cnt[mp[minv[i]]]--;
                    if(!vis[mp[minv[i]]])pq.push({cnt[mp[minv[i]]],mp[minv[i]]});
                }
            }
            break;
        }
    }
    
    for(int i = 2; i <= N; i++)if(!chk[i])ans[i]=maxv[i];
    for(int i = 2; i <= N; i++){
        cout << par[i] << ' ' << i << ' ' << ans[i] << '\n';
    }
}