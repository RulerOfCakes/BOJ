#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N;ll K;
const ll LNF = 2e18;
ll dsum[1010101];
__int128_t calc(__int128_t x, ll range){
    __int128_t tmp = x-range;
    return ((x*(x+1)/2)-(tmp*(tmp+1)/2));
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    vector<ll>v(N+1,0);
    for(int i = 1; i <= N; i++){
        cin >> v[i];
        dsum[i-1]=v[i]-v[i-1];
    }
    dsum[N]=LNF;

    ll l = 1, r = K/N+(bool)(K%N);
    while(l<r){
        ll mid = (l+r)/2;
        __int128_t tmp=0;
        for(int i = 1; i<=N; i++){
            tmp+=calc(mid,min(dsum[i],mid));
            if(tmp>=K)break;
        }
        if(tmp>=K)r=mid;
        else l = mid+1;
    }
    cout << l;
}