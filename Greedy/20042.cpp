#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    vector<ll> v(N, 0);
    
    vector<ll> dp(N, 0);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    ll ans = 0;
    for(int i = 0; i < N; i++){
        ll cans = 0;
        ll curmax = 0;
        if(i==0){
            curmax=v[i+1]-v[i];
        }
        else if(i==N-1){
            curmax = v[i]-v[i-1];
        }
        else{
            curmax = min(v[i]-v[i-1], v[i+1]-v[i]);
        }
        ll tcurmax = curmax;
        cans += curmax*curmax;
        for(int j = i-1; j >=0; j--){
            if(j==0){
                curmax=v[j+1]-curmax-v[j];
            }
            else
                curmax = min((v[j+1]-curmax)-v[j],v[j]-v[j-1]);
            cans+=curmax*curmax;
        }
        curmax=tcurmax;
        for(int j = i+1; j < N; j++){
            if(j==N-1){
                curmax=v[j]-(v[j-1]+curmax);
            } else {
                curmax = min(v[j]-(v[j-1]+curmax), v[j+1]-v[j]);
            }
            cans+=curmax*curmax;
        }
        ans = max(ans,cans);
    }
    cout << ans;
}