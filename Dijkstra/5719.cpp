#include <bits/stdc++.h>

using namespace std;

using pi = pair<int, int>;

int N, M, S, D;

bool popped[502][502];
vector<vector<pi>> v;
vector<vector<pi>> backwards;
vector<int> dist;
void dstra(){
    priority_queue<pi> pq;
    dist[S] = 0;
    pq.push({0, S});
    while(!pq.empty()){
        int cur = pq.top().second, val = -pq.top().first;
        pq.pop();
        if(dist[cur] < val)continue;
        if(cur == D){
            break;
        }
        for(auto a : v[cur]){
            int next = a.first, nextval = a.second;
            if(popped[cur][next])continue;
            if(val+nextval < dist[next]){
                pq.push({-(val + nextval), next});
                dist[next] = val+nextval;
            }
        }
    }
}

void trace(){
    queue<int> q;
    q.push(D);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if(cur == S)continue;
        for(auto a : backwards[cur]){
            int next = a.first, nextval = a.second;
            if(dist[cur] == dist[next] + nextval && !popped[next][cur]){
                popped[next][cur] = 1;
                q.push(next);
            }
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (1)
    {
        cin >> N >> M;
        if (!N && !M)
            return 0;
        for(int i = 0; i <= N; i++){
            for(int j = 0; j <= N; j++){
                popped[i][j] = 0;
            }
        }
        dist = vector<int>(N+1, INT_MAX);
        v = vector<vector<pi>>(N+1);
        backwards = vector<vector<pi>>(N+1);
        cin >> S >> D;
        for (int i = 0; i < M; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            v[a].push_back({b, c});
            backwards[b].push_back({a, c});
        }
        dstra();
        trace();
        for(int i = 0; i < N; i++){
            dist[i] = INT_MAX;
        }
        dstra();
        if(dist[D] == INT_MAX){
            cout << -1 << '\n';
        }
        else{
            cout << dist[D] << '\n';
        }
    }
}