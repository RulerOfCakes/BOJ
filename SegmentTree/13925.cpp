#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N,M;
const ll MOD = 1e9+7;
ll mulmod(ll a, ll b, ll mod = MOD) {
    ll res = 0; // Initialize result
    a = a % mod;
    while (b > 0)
    {
        // If b is odd, add 'a' to result
        if (b % 2 == 1)
            res = (res + a) % mod;
 
        // Multiply 'a' with 2
        a = (a * 2) % mod;

        // Divide b by 2
        b /= 2;
    }
    // Return result
    return res % mod;
}

namespace seg{
    //segment tree - with lazy update
    ll tree[1<<18];
    ll lazy[1<<18], lazy_mul[1<<18];
    int sz = 1<<17;

    void init(){
        for(int i = 0; i < (1<<18); i++){
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
            tree[node]%=MOD;
            if(s!=e){
                lazy[node * 2] += lazy[node];
                lazy[node*2]%=MOD;
                lazy[node * 2 + 1] += lazy[node];
                lazy[node*2+1]%=MOD;
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
        tree[node]=(tree[node*2]+tree[node*2+1])%MOD;
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
        tree[node]=(tree[node*2]+tree[node*2+1])%MOD;
    }

    void update_set(int node, int s, int e, int l, int r, ll v){
        update_lazy(node,s,e);
        if(r<s||e<l)return;
        if(l<=s&&e<=r){
            lazy_mul[node]=0;
            lazy[node]=v;
            update_lazy(node,s,e);
            return;
        }
        int mid=s+e>>1;
        update_set(node*2,s,mid,l,r,v);
        update_set(node*2+1,mid+1,e,l,r,v);
        tree[node]=(tree[node*2]+tree[node*2+1])%MOD;
    }

    ll query(int node, int s, int e, int l, int r){
        update_lazy(node,s,e);
        if(r<s||e<l)return 0;
        if(l<=s&&e<=r)return tree[node];
        int mid = s+e>>1;
        ll ret1 = query(node*2,s,mid,l,r), ret2 = query(node*2+1,mid+1,e,l,r);
        return (ret1+ret2)%MOD;
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    seg::init();
    for(int i = 0; i < N; i++){
        ll a;cin>>a;a%=MOD;
        seg::update_set(1,1,seg::sz,i+1,i+1,a);
    }
    cin>>M;
    for(int i = 0; i < M; i++){
        int a,b,c;
        ll d;
        cin>>a>>b>>c;
        if(a<4){
            cin>>d;
            d%=MOD;
            if(a==1){
                seg::update(1,1,seg::sz,b,c,d);
            } else if(a==2){
                seg::update_mul(1,1,seg::sz,b,c,d);
            } else {
                seg::update_set(1,1,seg::sz,b,c,d);
            }
        } else {
            cout << seg::query(1,1,seg::sz,b,c)%MOD << '\n';
        }
    }
}