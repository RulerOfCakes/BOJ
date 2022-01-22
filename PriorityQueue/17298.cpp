#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    vector<int> NGE(N+1,-1);
    for(int i = 0; i < N; i++){
        int a;cin>>a;   
        while(!pq.empty()&&pq.top().first<a){
            auto [cx, ci]=pq.top();
            pq.pop();
            NGE[ci]=a;
        }
        pq.push({a,i});
    }
    for(int i = 0; i < N; i++){
        cout << NGE[i] << ' ';
    }
}