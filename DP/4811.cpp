#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
ll dp[31][31];

ll sol(int full, int half){
    if(!full)return 1;
    ll& ret=dp[full][half];
    if(ret)return ret;
    return ret=sol(full-1, half+1)+(half?sol(full,half-1):0);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    while(N){
        cout << sol(N,0) << '\n';
        cin>>N;
    }
}