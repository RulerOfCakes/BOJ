#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int cnt[1000001];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll min, max;
    cin >> min >> max;
    for(int i = 0; i < max-min+1; i++){
        cnt[i]++;
    }
    int ans  = 0;
    for(ll i =2; i <= 1e6; i++){
        if(max<i*i)break;
        for(ll j = min/(i*i); j*i*i <= max; j++){
            if(i*i*j>=min)cnt[i*i*j-min]=0;
        }
    }
    for(int i = 0; i < max-min+1; i++){
        ans+=cnt[i];
    }
    cout << ans;
}