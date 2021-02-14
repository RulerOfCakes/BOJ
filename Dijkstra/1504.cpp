#include <bits/stdc++.h>

using namespace std;

int N, E;
int p1, p2;
//int dist[4][802];
vector<map<int, int>> ans;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> E;
    vector<pair<int, int>> v[N+1];
    int a, b, c;
    for(int i = 0; i < E; i++){
        cin >> a >> b >> c;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
    }
    cin >> p1 >> p2;
    
    for(int i : {1, p1, p2}){
        vector<bool> visitt(N+1, false);
        priority_queue<pair<int, int>> pq;
        map<int, int> mp;
        pq.push({0, i});
        while(!pq.empty()){
            int cur = pq.top().second, val = -pq.top().first;
            pq.pop();
            if(visitt[cur]){
                continue;
            }
            visitt[cur] = 1;
            if(cur == p1 || cur == p2 || cur == N){
                mp[cur] = val;
            }
            for(auto np : v[cur]){
                int next = np.first, nval = np.second;
                if(!visitt[next]){
                    pq.push({-(val + nval), next});
                }
            }
        }
        ans.push_back(mp);
    }
    auto startp1 = ans[0].find(p1), startp2 = ans[0].find(p2),
        p1top2 = ans[1].find(p2), p2top1 = ans[2].find(p1),
        p1toend = ans[1].find(N), p2toend = ans[2].find(N);
    int answer = INT_MAX;
    if(startp1 != ans[0].end() && p1top2 != ans[1].end() && p2toend != ans[2].end()){
        answer = startp1->second + p1top2->second + p2toend->second;
    }
    if(startp2 != ans[0].end() && p2top1 != ans[2].end() && p1toend != ans[1].end()){
        answer = min(answer, startp2->second + p2top1->second + p1toend->second);
    }
    if(answer == INT_MAX){
        answer = -1;
    }
    cout << answer;
}