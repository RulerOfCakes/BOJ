#include <bits/stdc++.h>
#define MAXN 500020
using namespace std;
using ll = unsigned int;
using pi = pair<int,int>;

//const ll MOD = (ll)INT_MAX+1LL;

// ll mulmod(ll a, ll b, ll mod) {
//     ll res = 0; // Initialize result
//     a = a % mod;
//     while (b > 0)
//     {
//         // If b is odd, add 'a' to result
//         if (b % 2 == 1)
//             res = (res + a) % mod;
 
//         // Multiply 'a' with 2
//         a = (a * 2) % mod;

//         // Divide b by 2
//         b /= 2;
//     }
//     // Return result
//     return res % mod;
// }
unsigned int mulmod(ll a, ll b){
    return a*b;
}
int N, M, Q;
namespace seg{
    //segment tree - with lazy update
    ll tree[1<<20];
    ll lazy[1<<20], lazy_mul[1<<20];
    int sz = 1<<19;

    void init(){
        for(int i = 0; i < (1<<20); i++){
            lazy_mul[i]=1;
        }
    }

    void update_lazy(int node, int s, int e){
        if(lazy_mul[node]!=1){
            tree[node]=mulmod(tree[node],lazy_mul[node]);
            if(s!=e){
                lazy[node<<1]=mulmod(lazy[node<<1],lazy_mul[node]);
                lazy_mul[node<<1]=mulmod(lazy_mul[node<<1],lazy_mul[node]);
                lazy[node<<1|1]=mulmod(lazy[node<<1|1],lazy_mul[node]);
                lazy_mul[node<<1|1]=mulmod(lazy_mul[node<<1|1],lazy_mul[node]);
            }
            lazy_mul[node]=1;
            //cout << "MUL" << node << ' ' << s << ' ' << e << ' ' << tree[node] << endl;
        }
        if(lazy[node]){
            tree[node]+=mulmod(e-s+1,lazy[node]);
            if(s!=e){
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node]=0;
            //cout << "LAZ" << node << ' ' << s << ' ' << e << ' ' << tree[node] << endl;
        }
    }

    void update(int node, int s, int e, int l, int r, ll v){
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
        tree[node]=(tree[node*2]+tree[node*2+1]);
    }

    void update_mul(int node, int s, int e, int l, int r, ll v){
        update_lazy(node,s,e);
        if(r<s||e<l)return;
        if(l<=s&&e<=r){
            lazy_mul[node]=v;
            update_lazy(node,s,e);
            return;
        }
        int mid=s+e>>1;
        update_mul(node*2,s,mid,l,r,v);
        update_mul(node*2+1,mid+1,e,l,r,v);
        tree[node]=(tree[node*2]+tree[node*2+1]);
    }

    ll query(int node, int s, int e, int l, int r){
        update_lazy(node,s,e);
        if(r<s||e<l)return 0;
        if(l<=s&&e<=r)return tree[node];
        int mid = s+e>>1;
        ll ret1 = query(node*2,s,mid,l,r), ret2 = query(node*2+1,mid+1,e,l,r);
        return (ret1+ret2);
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
        //different chainP
        if(depth[top[a]]<depth[top[b]])swap(a,b);
        int st=top[a];
        
        seg::update(1,1,seg::sz,in[st],in[a],val);
        a=par[st];
    }
    if(depth[a]>depth[b])swap(a,b);
    
    seg::update(1,1,seg::sz,in[a],in[b],val);
}

void update_mul(int a, int b, int val){
    while(top[a]!=top[b]){
        //different chainP
        if(depth[top[a]]<depth[top[b]])swap(a,b);
        int st=top[a];
        
        seg::update_mul(1,1,seg::sz,in[st],in[a],val);
        a=par[st];
    }
    if(depth[a]>depth[b])swap(a,b);
    
    seg::update_mul(1,1,seg::sz,in[a],in[b],val);
}

ll query(int a, int b){
    ll ret = 0;
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
    cin >> N >> Q;
    for(int i = 1; i <= N-1; i++){
        int a,b;
        cin >> a >> b;
        tadj[a].push_back(b);
        tadj[b].push_back(a);
    }
    top[1]=1;
    dfs();
    dfs1();
    dfs2();
    seg::init();
    for(int i = 0; i < Q; i++){
        int a,b,c,d;
        cin>>a>>b;
        switch(a){
            case 1:
            cin>>c;seg::update(1,1,seg::sz,in[b],out[b],c);
            break;
            case 2:
            cin>>c>>d;
            update(b,c,d);
            break;
            case 3:
            cin>>c;
            seg::update_mul(1,1,seg::sz,in[b],out[b],c);
            break;
            case 4:
            cin>>c>>d;
            update_mul(b,c,d);
            break;
            case 5:
            cout << seg::query(1,1,seg::sz,in[b],out[b]) << '\n';
            break;
            case 6:
            cin>>c;
            cout << query(b,c) << '\n';
            break;
            default: break;
        }
    }
    
}