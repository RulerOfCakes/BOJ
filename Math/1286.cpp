#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
using ll = long long;
int N,M;
vector<string> v;
ll ans[26];
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(0);
    cin>>N>>M;
    for(int i = 0 ; i < N; i++){
        string s;
        cin>>s;
        s+=s;
        v.push_back(s);
    }
    for(int i = 0; i < N; i++){
        v.push_back(v[i]);
    }
    
    N*=2;M*=2;
    for(int i = 0; i <N; i++){
        for(int j = 0; j < M; j++){
            ans[v[i][j]-'A']+=(ll)(N-i)*(i+1)*(j+1)*(M-j);
        }
    }
    for(int i = 0; i < 26; i++){
        cout << ans[i] << '\n';
    }
}