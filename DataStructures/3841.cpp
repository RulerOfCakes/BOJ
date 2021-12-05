#include <bits/stdc++.h>

using namespace std;
int N, M, K;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while(true){
        cin >> N;
        if(!N)break;
        deque<int> psum;
        vector<int> v(N);
        priority_queue<int,vector<int>,greater<int>>pq;
        map<int,int> mp;
        int prev=0;
        for(int i = 0; i < N; i++){
            cin >> v[i];
            psum[i]=prev+v[i];
            prev=psum[i];
            psum.push_back(psum[i]);
            pq.push(psum[i]);
        }
        int ans=(pq.top()>=0?1:0),off=0;
        for(int i = 1; i < N; i++){
            mp[psum.front()]++;
            psum.pop_front();
            off-=v[i-1];
            pq.push(v[i-1]+psum.back());
            psum.push_back(v[i-1]+psum.back());
            while(mp.count(pq.top())&&mp[pq.top()]>0){
                mp[pq.top()]--;
                pq.pop();
            }
            if(pq.top()+off>=0)ans++;
        }
        cout << ans << '\n';
    }
}