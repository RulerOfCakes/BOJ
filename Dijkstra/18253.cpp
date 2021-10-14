#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N, M;
const ll LNF = 1e18;

struct Query{
    int sx,sy,ex,ey;
}qry[100002];

struct emt{
    ll w;
    int x,y;
    bool operator<(const emt& t)const{
        if(w!=t.w)return w<t.w;
        if(x!=t.x)return x<t.x;
        return y<t.y;
    }
};

int arr[6][100002];
ll dist[6][100002];
ll ans[100002];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dstra(int sx,int sy, int l, int r){
    for(int i = 1; i <= N; i++){
        for(int j =l; j <= r; j++){
            dist[i][j]=LNF;
        }
    }
    priority_queue<emt> pq;
    pq.push({-arr[sx][sy],sx,sy});
    dist[sx][sy]=arr[sx][sy];
    while(!pq.empty()){
        int cx = pq.top().x,cy=pq.top().y;
        ll cc = -pq.top().w;
        pq.pop();
        if(dist[cx][cy]<cc)continue;
        for(int i = 0; i < 4; i++){
            int nx = cx+dx[i],ny=cy+dy[i];
            if(nx<1||nx>N||ny<l||ny>r)continue;
            ll nc = cc + arr[nx][ny];
            if(dist[nx][ny]<=nc)continue;
            dist[nx][ny]=nc;
            pq.push({-nc,nx,ny});
        }
    }
}
void sol(int l, int r, vector<int>&v){
    if(v.empty())return;
    if(l>r)return;
    int m = (l+r)/2;
    for(int i = 1; i <= N; i++){
        dstra(i,m,l,r);
        for(auto j : v){
            auto t = qry[j];
            ans[j]=min(ans[j],dist[t.sx][t.sy]+dist[t.ex][t.ey]-arr[i][m]);
        }
    }
    vector<int> lv,rv;
    for(auto i : v){
        if(qry[i].ey<m)lv.push_back(i);
        if(qry[i].sy>m)rv.push_back(i);
    }
    sol(l,m-1,lv);sol(m+1,r,rv);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> arr[i][j];
        }
    }
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        if(b>d){
            swap(a,c);swap(b,d);
        }
        qry[i]={a,b,c,d};
        ans[i]=LNF;
    }
    vector<int>v;
    for(int i = 0; i < Q; i++){
        v.push_back(i);
    }
    sol(1,M,v);
    for(int i = 0; i < Q; i++)cout << ans[i] << '\n';
}