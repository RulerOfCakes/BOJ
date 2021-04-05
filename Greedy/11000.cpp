#include <bits/stdc++.h>

using namespace std;
int N;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for(int i = 0; i < N; i++){
        int a, b;
        cin >> a >> b;
        pq.push({a, b});
    }
    priority_queue<int, vector<int>, greater<int>> ansv;
    int prog = 0;
    while(!pq.empty()){
        int curend = pq.top().second, curs = pq.top().first;
        pq.pop();
        if(ansv.empty()){
            ansv.push(curend);
            continue;
        }
        if(ansv.top()>curs){
            ansv.push(curend);
        } else {
            ansv.pop();
            ansv.push(curend);
        }
    }
    cout << ansv.size();
}