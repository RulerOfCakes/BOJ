#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool primes[101010];
vector<ll> primev;
ll multiples(vector<ll>& pv, int i, ll cx, ll bound){
    if(i==pv.size()||pv[i]*cx>bound)return 0;
    ll ret = (bound/pv[i])/cx;
    ret+=multiples(pv,i+1,cx,bound);
    ret-=multiples(pv,i+1,pv[i]*cx,bound);
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    for(int i = 2; i <= 100000; i++){
        if(!primes[i]){
            primev.push_back(i);
            for(int j = i*2; j <= 100000; j+=i){
                primes[j]=1;
            }
        }
    }
    int T;
    cin>>T;
    for(int t = 1; t <= T; t++){
        ll A,B,N;
        ll ans = 0;
        vector<ll> pv;
        cin>>A>>B>>N;
        for(int i = 0; i < primev.size() && N>1; i++){
            if(!(N%primev[i])){
                while(!(N%primev[i])&&N>1){
                    N/=primev[i];
                }
                pv.push_back(primev[i]);
            }
        }
        if(N!=1){
            pv.push_back(N);
        }
        ans = (B-A+1) - (multiples(pv,0,1,B) - multiples(pv,0,1,A-1));
        cout << "Case #" << t << ": " << ans << '\n';
    }
}