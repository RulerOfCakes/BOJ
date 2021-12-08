#include <bits/stdc++.h>

using namespace std;

using Edge = tuple<int, int, int>;
using pi = pair<int, int>;

int T, M, W, N;
const int INF = 1e9;
vector<Edge> v;
vector<int> dist;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool Bellman_Ford(int s){
    int a, b, t;
    dist[s]=0;

    for(int i = 1; i <= N; i++){
        for(Edge e:v){
            tie(a, b, t) = e;
            //if(dist[a]==INF)continue;
            dist[b] = min(dist[b], dist[a] + t);
        }
    }
    
    for(Edge e:v){
        tie(a, b, t) = e;
        if(dist[b] > dist[a]+t){
            //if(dist[a]==INF)continue;
            return true;
        }
    }
    
    return false;
}

//different constraints system
//partial sum [a, b] = c -> psum[b]-psum[a-1]=c
//0 <= psum[i+1]-psum[i] <= 1

int main(){
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >>N >> M>> W;
        dist=vector<int>(N+2,INF);
        v=vector<Edge>();
        for(int i = 0; i < M; i++){
            int a,b,c;
            cin >> a >> b >> c;
            v.push_back({a,b,c});
            v.push_back({b,a,c});
        }
        for(int i = 0 ; i < W; i++){
            int a,b,c;
            cin >> a >>b >> c;
            v.push_back({a,b,-c});
        }
        if(Bellman_Ford(1)){
            cout << "YES\n";
        }
        else cout << "NO\n";
    }

}