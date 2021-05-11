#include <bits/stdc++.h>

using namespace std;
int W, H, G, E;
const int INF = 1e9;
using Edge = tuple<int, int, int, int, int>;
using pi = pair<int, int>;

vector<Edge> v;
vector<vector<int>> dist;
vector<vector<int>> tomb;
vector<vector<int>> ghost;
map<pi, pi> ghostmp;
vector<vector<int>> neg;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool Bellman_Ford(int sx, int sy){
    int a, b, c, d, t;
    dist[sx][sy]=0;

    for(int i = 1; i <= W*H-1; i++){
        for(Edge e:v){
            tie(a, b, c, d, t) = e;
            if(dist[a][b]==INF)continue;
            dist[c][d] = min(dist[c][d], dist[a][b] + t);
        }
    }
    
    for(Edge e:v){
        tie(a, b, c, d, t) = e;
        if(dist[c][d] > dist[a][b]+t){
            if(dist[a][b]==INF)continue;
            else return true;
        }
    }
    
    return false;
}

int main(){
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while(true){
        cin >> W >> H;
        if(W==0&&H==0)break;
        dist = vector<vector<int>>(W+1, vector<int>(H+1, INF));
        tomb = vector<vector<int>>(W+1, vector<int>(H+1, 0));
        ghost = vector<vector<int>>(W+1, vector<int>(H+1, 0));
        neg = vector<vector<int>>(W+1, vector<int>(H+1, 0));
        ghostmp = map<pi, pi>();
        v = vector<Edge>();
        cin >> G;
        
        for(int i = 0; i < G; i++){
            int a, b;
            cin >> a >> b;
            tomb[a][b]=-1;
        }
        cin >> E;
        for(int i = 0; i < E; i++){
            int a, b, c, d, t;
            cin >> a >> b >> c >> d >> t;
            ghost[a][b]=-1;
            ghostmp[{a, b}] = {c, d};
            v.push_back({a, b, c, d, t});
        }
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){
                if(tomb[i][j]==-1||ghost[i][j]==-1)continue;
                if((i==W-1) && (j == H-1))continue;
                for(int k = 0; k < 4; k++){
                    int nx = i + dx[k], ny = j + dy[k];
                    if(nx<0||nx>=W||ny<0||ny>=H)continue;
                    if(tomb[nx][ny]==-1)continue;
                    v.push_back({i, j, nx, ny, 1});
                }
            }
        }
        


        bool va = Bellman_Ford(0, 0);

        if(va){
            cout << "Never\n";
        }
        else if(dist[W-1][H-1]==INF){
            cout << "Impossible\n";
        } else {
            cout << dist[W-1][H-1] << '\n';
        }
    }
}