#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = tuple<double, int, int>;

int N;
priority_queue<Edge> ev;
int parent[102];

int find(int node){
    if(node==parent[node]){
        return node;
    }
    return parent[node]=find(parent[node]);
}

void uni(int a, int b){
    int ar=find(a), br=find(b);

    parent[br]=ar;
}
vector<pair<double,double>> arr;

double getdist(double x, double y){
    return sqrt(x*x+y*y);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i <= N; i++){
        parent[i]=i;
    }
    for(int i = 0; i < N; i++){
        double a,b;
        cin >> a >> b;
        arr.push_back({a,b});
    }
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            ev.push(make_tuple(-getdist(arr[i].first-arr[j].first,arr[i].second-arr[j].second),i,j));
        }
    }
    
    double ans = 0;
    while(!ev.empty()){
        double weight;int x, y;
        tie(weight, x, y) = ev.top();
        weight = -weight;
        ev.pop();
        if(find(x)!=find(y)){
            uni(x,y);
            ans+=weight;
            
        }
    }    
    cout << ans;
}