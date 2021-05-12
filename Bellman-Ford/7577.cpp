#include <bits/stdc++.h>

using namespace std;

using Edge = tuple<int, int, int>;
using pi = pair<int, int>;

int K, N;
const int INF = 1e9;
vector<Edge> v;
vector<int> dist;


int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool Bellman_Ford(int s){
    int a, b, t;
    dist[s]=0;

    for(int i = 1; i <= K; i++){
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
    cin >> K >> N;
    dist = vector<int>(K+2,INF);
    for(int i = 0; i < N; i++){
        int a, b, c;
        cin >> a >> b >> c;
        v.push_back({a-1, b, c});
        v.push_back({b, a-1, -c});
    }
    for(int i = 0; i <= K; i++){
        if(i>0){
            v.push_back({i-1, i, 1});
            v.push_back({i, i-1, 0});
        }
        v.push_back({K+1, i, 0});
    }
    
    if(Bellman_Ford(K+1))cout<<"NONE";
    else{
        for(int i = 1; i <= K; i++){
            if(dist[i]==dist[i-1])cout << '-';
            else cout << '#';
        }
    }
}