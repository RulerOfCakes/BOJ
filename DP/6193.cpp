#include <bits/stdc++.h>

using namespace std;

int N;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> dp(1,-1);
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        if(a>dp.back())dp.push_back(a);
        else *lower_bound(dp.begin(),dp.end(),a) = a;
    }
    cout << dp.size()-1;
}