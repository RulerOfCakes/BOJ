#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
int cnt[101010];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    int a;
    for(int i = 0; i < N; i++){
        cin >> a;
        cnt[a]++;
    }
    ll ans=0;
    for(int i = 1e5; i >= 1; i--){
        if(cnt[i]){
            int j;
            for(j = i; j >=1&&cnt[j]; --cnt[j--]);
            ans+=(ll)i*(i-j);
            i++;
        }
    }
    cout << ans;
}