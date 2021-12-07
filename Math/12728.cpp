#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
using vl = vector<vector<ll>>;
int N,T;
const int MOD = 1000;
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
    cin >> T;
    for(int i = 1; i <= T; i++){
        cin >> N;
        //vl v(2,vector<ll>(2));
        vl v = {
            {6,-4},
            {1,0}
        };
        v=pow(v,N-1);
        int ans = ((v[1][0]*28)%MOD+(6*v[1][1])%MOD-1+MOD)%MOD;

        string ret = to_string(ans);
        while(ret.size()<3){
            ret='0'+ret;
        }
        cout << "Case #" << i << ": " << ret << '\n';
    }
}