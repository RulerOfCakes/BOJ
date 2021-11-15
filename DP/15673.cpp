#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
int arr[100002],psum[100002];
//maximum range sum available with endpoint as i -> maxx[i]
int maxx[100002],minn[100002];
multiset<int> psums;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
        psum[i]=psum[i-1]+arr[i];
        if(i>=2)psums.insert(psum[i]);
    }
    int tmax=0,tmin=0;
    for(int i = 1; i <= N; i++){
        maxx[i]=psum[i]-tmin;
        minn[i]=psum[i]-tmax;
        tmax=max(tmax,psum[i]);
        tmin=min(tmin,psum[i]);
    }
    ll ans = -2e9;
    //previous minimum/maximum group sums
    tmax=maxx[1],tmin=minn[1];
    for(int i = 2; i <= N; i++){
        //minimum/maximum starting from i
        ll cmin = *psums.begin()-psum[i-1];
        auto iter=psums.end();iter--;
        ll cmax = *iter - psum[i-1];
        ans=max(ans,max(cmin*tmin,cmax*tmax));
        psums.erase(psums.find(psum[i]));
        tmax=max(tmax,maxx[i]);
        tmin=min(tmin,minn[i]);
    }
    cout << ans;
}