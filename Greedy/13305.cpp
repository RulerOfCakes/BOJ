#include <bits/stdc++.h>

using namespace std;

int N;
bool passed[100002];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int a;
    long long min = 0;
    vector<int> roads;
    priority_queue<pair<int, int>> pq;

    for(int i = 1; i < N; i++){
        cin >> a;
        roads.push_back(a);
    }
    roads.push_back(0);
    for(int i = 1; i <= N; i++){
        cin >> a;
        pq.push({-a, i});
    }
    while(!pq.empty()){
        int cur = -pq.top().first, idx = pq.top().second;
        pq.pop();
        if(passed[idx])continue;
        for(int i = idx; i <= N&&!passed[i]; i++){
            passed[i] = 1;
            min += 1LL*cur*roads[i-1];
        }
    }
    cout << min;
}