#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N;
const ll LNF = 1e18;
vector<vector<int>> adj(202020);
ll cnt;
ll l[202020],r[202020];
ll ans[202020];
void dfs(int cx){
    l[cx]=++cnt;
    ll prev=l[cx];
    for(int nx:adj[cx]){
        dfs(nx);
    }
    r[cx]=cnt;

    ll totcnt=r[cx]-l[cx];
    for(int nx:adj[cx]){
        ans[cx]+=(r[nx]-l[nx]+1)*(totcnt-(r[nx]-l[nx]+1));
    }
    ans[cx]+=(r[cx]-l[cx])*2+1;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    int root;
    for(int i = 0; i < N; i++){
        int a;cin>>a;
        if(!a)root=i+1;
        else{
            adj[a].push_back(i+1);
        }
    }
    dfs(root);
    ll ans1=0,ans2=0;
    bool flip=0;
    for(int i = 1; i <= N; i++){
        if(!ans[i])continue;
        if(flip){
            if(ans[i]%2==0){
                ans1+=ans[i]/2*i;
                ans2+=ans[i]/2*i;
            }
            else{
                ans1+=ans[i]/2*i;
                ans2+=(ans[i]/2+1)*i;
                flip=!flip;
            }
        }
        else{
            if(ans[i]%2==0){
                ans1+=ans[i]/2*i;
                ans2+=ans[i]/2*i;
            }
            else{
                ans1+=(ans[i]/2+1)*i;
                ans2+=ans[i]/2*i;
                flip=!flip;
            }
        }
    }
    cout<<ans2<< ' '<<ans1;
}