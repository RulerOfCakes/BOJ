#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, M;
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    deque<pi> dq;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        while(!dq.empty()&&dq.front().second<i-M+1)dq.pop_front();
        while(!dq.empty()&&dq.back().first > a)dq.pop_back();
        dq.push_back({a, i});
        cout << dq.front().first << ' ';
    }
    
}