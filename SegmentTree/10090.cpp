#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;

int N;

class segtree{
    public:
    vector<ll> tree;
    int size;
    segtree(int n){
        for(size=1;size<=n;size*=2);
        tree.resize(size*2,0);
    }
    void update(int pos, ll x){
        int idx = pos+size-1;
        ll diff = x-tree[idx];
        while(idx){
            tree[idx]+=diff;
            idx/=2;
        }
    }
    ll getsum(int node, int s, int e, int l, int r){
        if(s>r||e<l)return 0;
        if(l<=s&&e<=r)return tree[node];
        int mid = s+e>>1;
        return getsum(node*2,s,mid,l,r)+getsum(node*2+1,mid+1,e,l,r);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> N;
    segtree seg(N+1);
    ll ans = 0;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        ans+=seg.getsum(1,1,seg.size,a+1,N);
        seg.update(a,1);
    }
    cout << ans;
}