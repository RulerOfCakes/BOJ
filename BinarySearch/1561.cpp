#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N, M;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c;
    
    cin >> N >> M;
    vector<ll> minutes(M, 0);
    for(int i = 0; i < M; i++){
        cin >> minutes[i];
    }

    ll lo = 0, hi = 2e11;
    if(N<=M){
        cout << N;
        return 0;
    }

    while(lo<hi){
        ll mid = (lo+hi)>>1;
        ll temp = 0;
        for(int i = 0; i < M; i++){
            temp += mid/minutes[i];
        }
        temp += M;
        if(temp >= N){
            hi=mid;
            
        }
        else{
            lo = mid+1;
        }
    }
    lo--;
    ll ridenum = 0;
    for(int i = 0; i < M; i++){
        ridenum += lo/minutes[i];
    }
    ridenum+=M;
    lo++;
    for(int i = 0; i < M; i++){
        if(!(lo%minutes[i])){
            ridenum++;
        }
        if(ridenum==N){
            cout << i+1;
            return 0;
        }
    }
}