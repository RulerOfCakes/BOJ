#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
using vl = vector<vector<ll>>;
int N;
const int MOD = 1e9 + 7;
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
    cin >> N;
    vl v = {
        {0, 1, 0, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 1, 1, 0},
        {1, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 1, 0}};
    v = pow(v, N);
    cout << v[0][0];
}