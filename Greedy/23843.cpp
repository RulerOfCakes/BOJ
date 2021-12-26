#include <bits/stdc++.h>
using namespace std;
int N,M;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    priority_queue<int> pq;
    priority_queue<int,vector<int>,greater<int>> rpq;
    for(int i = 0; i < N; i++){
int a;cin>>a;pq.push(a);
    }
    for(int i = 0; i < min(N,M); i++){
        int cx=pq.top();
        pq.pop();
        rpq.push(cx);
    }
    int ans=0;
    while(!rpq.empty()){
        int cx=rpq.top();rpq.pop();
        ans=max(ans,cx);
        if(!pq.empty()){
            int nx=pq.top();pq.pop();
            rpq.push(cx+nx);
        }
    }
    cout << ans;
}