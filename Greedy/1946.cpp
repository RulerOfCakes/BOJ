#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, T;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> T;
    while(T--){
        cin >> N;
        vector<pi> v;
        for(int i = 1; i <= N; i++){
            int a, b;
            cin >> a >> b;
            v.push_back({a, b});
        }
        sort(v.begin(), v.end());
        int ans = 1, minterview = v[0].second;
        for(int i = 1; i < N; i++){
            if(v[i].second > minterview){
                continue;
            }
            else{
                ans++;
                minterview = min(minterview, v[i].second);
            }
        }
        cout << ans << '\n';
    }
}