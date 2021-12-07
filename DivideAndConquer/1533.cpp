#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
using vl = vector<vector<ll>>;
int N,S,E,T;
const int MOD = 1e6 + 3;
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
vl pow(vl a, int n)
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
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> S >> E >> T;
    vl v(5*N+1,vector<ll>(5*N+1));
    for(int i = 0; i < N; i++){
        for(int k = 1; k < 5; k++){
            v[i*5+k][i*5+k+1]=1;
        }
    }
    for(int i = 1; i <= N; i++){
        string s;
        cin>>s;
        for(int j =0 ; j < N; j++){
            if(s[j]=='0')continue;
            int val=s[j]-'0'-1;
            v[i*5][(j+1)*5-val]=1;
        }
    }
    
    v = pow(v, T);
    cout << v[5*S][5*E];
}