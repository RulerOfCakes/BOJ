#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = tuple<int, int, int>;
const int MINF = -1e9-1;
int N, M;
priority_queue<Edge> ev;
int parent[100002];

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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    for(int i = 0; i <= N; i++){
        parent[i]=i;
    }
    vector<Edge> xv,yv,zv;
    map<Edge, int>mp;
    for(int i = 0; i < N; i++){
        int a,b,c;
        cin >> a >> b >> c;
        mp[{a,b,c}]=i+1;
        xv.push_back({a,b,c});
        yv.push_back({b,a,c});
        zv.push_back({c,a,b});
    }
    sort(xv.begin(),xv.end());
    sort(yv.begin(),yv.end());
    sort(zv.begin(),zv.end());
    Edge prev={MINF,MINF,MINF};
    Edge MINE=prev;
    for(int i = 0; i < N; i++){
        Edge ce=xv[i];
        int x,y,z;
        tie(x,y,z)=ce;
        if(prev==MINE){prev=ce;continue;}
        int px,py,pz;tie(px,py,pz)=prev;
        ev.push({-abs(px-x),mp[ce],mp[prev]});
        prev=ce;
    }
    prev=MINE;
    for(int i = 0; i < N; i++){
        Edge ce=yv[i];
        int x,y,z;
        tie(y,x,z)=ce;
        if(prev==MINE){prev=ce;continue;}
        int px,py,pz;tie(py,px,pz)=prev;
        ev.push({-abs(py-y),mp[{x,y,z}],mp[{px,py,pz}]});
        prev=ce;
    }
    prev=MINE;
    for(int i = 0; i < N; i++){
        Edge ce=zv[i];
        int x,y,z;
        tie(z,x,y)=ce;
        if(prev==MINE){prev=ce;continue;}
        int px,py,pz;tie(pz,px,py)=prev;
        ev.push({-abs(pz-z),mp[{x,y,z}],mp[{px,py,pz}]});
        prev=ce;
    }

    ll ans = 0;
    while(!ev.empty()){
        int weight, x, y;
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