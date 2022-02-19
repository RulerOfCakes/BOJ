#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ans[1010101];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int N,T;
    
    fill(ans,ans+1000002,1);
    for(int i = 2; i <= 1e6; i++){
        for(int j = 1; i*j<=1e6; j++)ans[i*j]+=i;
    }
    for(int i = 2; i <= 1e6; i++)ans[i]+=ans[i-1];
    cin>>T;
    while(T--){
        cin>>N;
        cout << ans[N] << '\n';
    }
}