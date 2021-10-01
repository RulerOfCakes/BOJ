#include <bits/stdc++.h>

using namespace std;

using Edge = tuple<int, int, int>;
using pi = pair<int, int>;

int N, ML, MD;
const int INF = 1e9+1e8;

vector<Edge> v;
vector<int> dist;

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
    cin >> N >> ML >> MD;
    dist = vector<int>(N+2,INF);
    for(int i = 0; i < ML; i++){
        int a,b,c;
        //b-a<c
        cin >> a >> b >> c;
        //v.push_back({b,a,-c});
        v.push_back({a,b,-c});
    }
    for(int i = 0; i < MD; i++){
        int a,b,c;
        //b-a>c   a-b<c
        cin >> a >> b >> c;
        v.push_back({b,a,-c});
        //v.push_back({a,b,c});
    }
    
    for(int i = 0; i <= N; i++){
        if(i>0){
            //i-(i-1)>0  (i-1)-i < 0
            v.push_back({i, i-1, 0});
        }
        v.push_back({N+1, i, 0});
    }
    
    
    if(Bellman_Ford(N+1))cout<<"-2";
    else{
        for(int i = 0; i <= N; i++){
            //cout << dist[i] << ' ';
            if(dist[i]==INF){
                cout << -1;
                return 0;
            }
        }
        cout << abs(dist[N]-dist[1]);
    }
}