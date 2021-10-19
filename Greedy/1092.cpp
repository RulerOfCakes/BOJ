#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, M, K;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;vector<int>v(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    sort(v.begin(),v.end(),greater<int>());
    cin >> M;multiset<int>box;
    for(int i = 0; i < M; i++){
        int a;
        cin >> a; box.insert(a);
    }
    for(int i = 1; i <= 10001; i++){
        for(int j = 0; j < N; j++){
            auto iter = box.upper_bound(v[j]);
            if(iter==box.begin())break;
            iter--;box.erase(iter);
            if(box.empty())break;
        }
        if(box.empty()){
            cout << i;
            return 0;
        }
    }
    cout << -1;
}