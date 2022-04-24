#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int N,K,zeros=0;
    cin>>N>>K;deque<pi>v(2*N,{0,0});
    for(int i = 0; i < 2*N; i++){
        cin>>v[i].first;
        if(v[i].first==0)zeros++;
    }
    int ans = 0;
    while(zeros<K){
        ans++;
        pi pb = v.back();
        v.pop_back();
        v.push_front(pb);
        if(v[N-1].second)v[N-1].second=0;
        for(int i = N-2; i >= 0; i--){
            if(v[i].second&&v[i+1].first&&!v[i+1].second){
                v[i].second=0;
                v[i+1].first--;
                v[i+1].second++;
                if(v[i+1].first==0)zeros++;
                if(i+1==N-1){
                    v[i+1].second--;
                }
            }
        }
        if(v[0].first){
            v[0].first--;
            if(v[0].first==0)zeros++;
            v[0].second++;
        }
    }
    cout<<ans;
}