#include <bits/stdc++.h>

using namespace std;
using ll = long long;


const int INF = 1e9+7;


class segtree{
public:
    vector<ll> tree;
    vector<int> idxs;
    int size;
    segtree(int n){
        for(size=1;size<=n;size*=2);
        tree.resize(size*2,INF);
        idxs.resize(size*2,0);
        for(int i = size; i < size*2; i++){
            idxs[i]=i-size+1;
        }
    }
    void update(int pos, ll x){
        int idx = pos+size-1;
        tree[idx]=x;
        idx/=2;
        while(idx){
            tree[idx]=min(tree[idx*2],tree[idx*2+1]);
            if(tree[idx]==tree[idx*2]){
                idxs[idx]=idxs[idx*2];
            }
            else{
                idxs[idx]=idxs[idx*2+1];
            }
            idx/=2;
        }
    }
    ll getval(int pos){
        if(pos==0)return INF;
        return tree[pos+size-1];
    }
    ll getminidx(int node, int s, int e, int l, int r){
        if(l<=s&&e<=r)return idxs[node];
        if(r<s||e<l)return 0;
        int mid = s+e>>1;
        ll t1=getminidx(node*2,s,mid,l,r),t2=getminidx(node*2+1,mid+1,e,l,r);
        if(getval(t1)<=getval(t2)){
            return t1;
        }
        else return t2;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int N;
    cin >> N;
    segtree seg(N+1);
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        seg.update(i+1,a);
    }
    int M;
    cin >> M;
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        if(a==1){
            seg.update(b,c);
        }
        else{
            cout << seg.getminidx(1,1,seg.size,b,c)<<'\n';
        }
    }
}