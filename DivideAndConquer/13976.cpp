#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<vector<ll>>;

ll N;
const int MOD = 1e9+7;
//matrix multiplication
vl operator*(vl const &a, vl const &b)
{
    vl ret(a.size(), vector<ll>(b[0].size()));
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            for (int k = 0; k < b[0].size(); k++)
            {
                ret[i][k] = (ret[i][k] + a[i][j] * b[j][k]) % MOD;
            }
        }
    }
    return ret;
}
//matrix exponentiation
vl pow(vl a, ll n)
{
    vl ret(a.size(), vector<ll>(a.size()));
    for(int i = 0; i < a.size(); i++){
        ret[i][i]=1;
    }
    while(n){
        if(n&1)ret=ret*a;
        n>>=1;
        a=a*a;
    }
    return ret;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    if(N%2)cout << 0;
    else{
        //dp[n]=4*dp[n-2]-dp[n-4];
        vl v={{4,-1},{1,0}};
        vl sv={{3},{1}};
        cout << ((pow(v,(N-2)/2)*sv)[0][0]+MOD)%MOD;
    }
}