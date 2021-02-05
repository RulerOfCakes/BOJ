#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    priority_queue<int> pq;
    for(int i = 0; i < N*N; i++){
        int a;
        cin >> a;
        pq.push(-a);
        if(pq.size() > N)pq.pop();
    }
    cout << -pq.top();
}