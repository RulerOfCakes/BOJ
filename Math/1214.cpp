#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll D,P,Q;
ll gcd(ll a, ll b){
    if(!b)return a;
    return gcd(b,a%b);
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>D>>P>>Q;
    if(P>Q)swap(P,Q);
    ll g = gcd(P,Q);
    // proved from coin problem, if P and Q are coprimes any number above (P-1)(Q-1) can be represented
    ll tmp = g!=1?g*(P/g-1)*(Q/g-1):(P-1)*(Q-1);
    if(tmp<=D){
        //cout << g << endl;
        cout << g*(D/g+(bool)(D%g));
    }
    else {
        ll ans = (D/P+(bool)(D%P))*P;
        //cout << ans << endl;
        bool done=0;
        for(int i = 1; !done; i++){
            if(i*Q>=D){
                done=1;
                ans=min(ans,i*Q);
                break;
            }
            ans=min(ans,i*Q+(ll)(((D-i*Q)/P+(bool)((D-i*Q)%P))*P));
        }
        cout << ans;
    }
}