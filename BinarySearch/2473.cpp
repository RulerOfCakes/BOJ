#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N;
const ll INF = 1e15;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<ll>v(N,0);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    sort(v.begin(),v.end());
    ll ans1,ans2,ans3;
    ll sum = INF;
    for(int i = 0; i < N-2; i++){
        int c = i, l = i+1, r = N-1;
        
        while(l<r){
            ll tsum = v[c]+v[l]+v[r];
            
            if(abs(tsum)<sum){
                sum=abs(tsum);
                
                ans1=v[c],ans2=v[l],ans3=v[r];
            }
            if(tsum<0)l++;
            else if(tsum>0)r--;
            else{
                i=N;
                break;
            }
        }
    }
    cout << ans1 << ' ' << ans2 << ' ' << ans3;
}