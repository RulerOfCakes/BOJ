#include <bits/stdc++.h>

using namespace std;

int N;
int arr[1000002];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i+1];
    }
    vector<int> dp(1,-1e9-2);
    for(int i = 1; i <= N; i++){
        if(dp.back()<arr[i])dp.push_back(arr[i]);
        else *lower_bound(dp.begin(),dp.end(),arr[i])=arr[i];
    }
    cout << dp.size()-1;
}