#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    vector<pi>v(N);
    for(int i = 0; i < N; i++){
        cin >> v[i].first;
        v[i].second=i;
    }
    int ans = 0;
    sort(v.begin(),v.end());
    for(int i = 0; i < N; i++){
        ans=max(ans,v[i].second-i);
    }
    cout << ans+1 << '\n';
}