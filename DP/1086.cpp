#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll dp[1<<16][102];

int N, K;

ll gcd(ll x, ll y){
    if(!y)return x;
    return gcd(y, x%y);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    vector<string> v(N);
    vector<int> mods(N,0);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    cin >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < v[i].size(); j++){
            mods[i] = mods[i]*10+(v[i][j]-'0');
            mods[i]%=K;
        }
    }
    vector<int> premods(51);
    premods[0]=1;
    for(int i = 1; i <= 50; i++){
        premods[i]=premods[i-1]*10;
        premods[i]%=K;
    }
    dp[0][0]=1;
    for(int i = 0; i < (1<<N); i++){
        for(int j = 0; j < K; j++){
            for(int k = 0; k < N; k++){
                if((i&(1<<k))==0){
                    //nxt = (newnum)%K = (originalnum*pow(10,v[k].size())+stoi(v[k])))%k
                    int nxt = j*premods[v[k].size()];
                    nxt%=K;
                    nxt+=mods[k];
                    nxt%=K;
                    dp[i|(1<<k)][nxt]+=dp[i][j];
                }
            }
        }
    }
    ll ans1 = dp[(1<<N)-1][0], ans2 = 1;
    
    //N!
    for(ll i = 2; i <= N; i++){
        ans2 *= i;
    }
    ll tmod = gcd(ans1,ans2);
    ans1/=tmod;ans2/=tmod;
    cout << ans1 << "/" << ans2;
}