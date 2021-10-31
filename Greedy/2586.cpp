#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pl = pair<ll, ll>;
using pi = pair<int,int>;
const int INF = 1e9;
int T,N,M;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
        
    cin >> N >> M;
    int K = N+M;
    vector<pi> v(N+M);
    int a;
    for(int i = 0; i < N; i++){
        cin >> a;
        v[i]={a,0};
    }
    for(int j = 0; j < M; j++){
        cin >> a;
        v[N+j]={a,1};
    }
    sort(v.begin(),v.end());
    vector<vector<pi>> tree(2*K+2, vector<pi>());
    int now = K;
    for(int i = 0; i < K; i++){
        if(v[i].second==0)tree[now++].push_back(v[i]);
        else tree[--now].push_back(v[i]);
    }
    int ans = 0;
    for(int i = 0; i < tree.size(); i++){
        if(!tree[i].empty()){
            int cval=0;
            //match each pump/firetruck in order
            for(int j = 1; j < tree[i].size(); j+=2){
                cval+=abs(tree[i][j].first-tree[i][j-1].first);
            }
            //cout << cval << '\n';
            //if total number of entries in this layer is even, no problem
            if(!(tree[i].size()&1)){
                ans+=cval;continue;
            }
            //else we need to find maximum matching while excluding one entry
            int mval=cval;
            for(int j = tree[i].size()-1; j-2>=0; j-=2){
                //recalculating sum if j-2 is excluded
                cval+=abs(tree[i][j].first-tree[i][j-1].first)-abs(tree[i][j-1].first-tree[i][j-2].first);
                mval=min(mval,cval);
            }
            ans+=mval;
            //cout << ans << '\n';
        }
    }
    cout << ans;
}