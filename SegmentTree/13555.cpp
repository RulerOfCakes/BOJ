#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int MOD = 5e6;
int N, K;
int dp[51][100002];
class fwtree
{
public:
    vector<vector<int>> tree;
    
    fwtree(int n)
    {
        
        tree.resize(51, vector<int>(100002));
        //lazy.resize(size * 2);
        //cnt.resize(size * 2);
        //sum.resize(size * 2);
    }
    void update(int k, int node, long long x)
    {
        while(node<=100000){
            tree[k][node]=(x+tree[k][node])%MOD;
            
            node += (node&-node);
        }
    }
    //[1,i]
    int sum(int k, int i){
        int ans = 0;
        if(k==0)return 1;
        while(i){
            ans=(tree[k][i]+ans)%MOD;
            //removing the last 1 in binary
            i-=(i&-i);
        }
        return ans;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> K;
    fwtree fw(N+1);
    vector<int> v(N+1);
    for (int i = 1; i <= N; i++)
    {
        cin >> v[i];
    }
    
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= K; j++){
            dp[j][i]=fw.sum(j-1,v[i]-1);
            
            fw.update(j,v[i],dp[j][i]);
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        ans=(ans+dp[K][i])%MOD;
    }
    cout << ans;
}