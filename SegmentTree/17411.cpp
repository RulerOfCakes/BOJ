#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<int,int>;

int N, M;
const int INF = 1e9+7;

pi pimax(const pi p1,const pi p2){
    if(p1.first==p2.first){
        return{p1.first,(p1.second+p2.second)%INF};
    }
    else return max(p1,p2);
}

class segtree{
public:
    vector<pi> tree;
    
    int size;
    segtree(int n){
        for(size=1;size<=n;size*=2);
        tree.resize(size*2);
    }
    void update(int pos, pi x){
        int idx=pos+size-1;
        tree[idx]=pimax(tree[idx],x);
        idx/=2;
        while(idx){
            tree[idx]=pimax(tree[idx*2],tree[idx*2+1]);
            idx/=2;
        }
    }
    pi getmax(int node, int s, int e, int l, int r){
        if(s>r||e<l)return {0,0};
        if(l<=s&&e<=r)return tree[node];
        int mid = s+e>>1;
        return pimax(getmax(node*2,s,mid,l,r),getmax(node*2+1,mid+1,e,l,r));
    }
    
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    segtree seg(1e6+2);
    vector<int> ov,v;
    map<int,int> mp;
    int a;
    for(int i = 0; i < N; i++){
        cin >> a;
        ov.push_back(a);
        v.push_back(a);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i = 0; i < v.size(); i++){
        mp[v[i]]=i+2;
    }
    pi ansp={0,0};
    for(int i = 0; i < N; i++){
        ov[i]=mp[ov[i]];
        pi tp = seg.getmax(1,1,seg.size,1,ov[i]-1);
        if(tp==pi(0,0))tp={1,1};
        else tp.first++;
        ansp=pimax(ansp,tp);
        seg.update(ov[i],tp);
    }
    cout << ansp.first << ' ' << ansp.second;
}