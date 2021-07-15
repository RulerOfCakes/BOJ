#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class edge
{
public:
    int u, v;
    double w;
    edge(int a, int b, double c){
        u=a;v=b;w=c;
    }
    bool operator<(const edge &e) const
    {
        return w < e.w;
    }
    bool operator>(const edge &e) const{
        return w > e.w;
    }
};

int T, N, W;

int parent[100002];

int find(int node)
{
    if (node == parent[node])
    {
        return node;
    }
    return parent[node] = find(parent[node]);
}

void uni(int a, int b)
{
    int ar = find(a), br = find(b);

    parent[br] = ar;
}

double dist(int x1, int y1, int x2, int y2){
    return sqrt(1LL*(x1-x2)*(x1-x2) + 1LL*(y1-y2)*(y1-y2));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while (T--)
    {
        cin >> W >> N;
        priority_queue<edge,vector<edge>,greater<edge>> ev;
        vector<pair<int, pair<int,int>>> v;
        for (int i = 0; i <= N+1; i++)
        {
            parent[i] = i;
        }
        ev.push(edge(0,N+1,(double)W));
        for (int i = 1; i <= N; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            v.push_back({c,{a,b}});
            ev.push(edge(0,i,max((double)(a-c),(double)0)));
            ev.push(edge(i,N+1,max((double)(W-a-c),(double)0)));
            for(int j = 1; j < i; j++){
                ev.push(edge(j,i,max(dist(a,b,v[j-1].second.first,v[j-1].second.second)-c-v[j-1].first,(double)0)));
            }
        }
        
        while (!ev.empty())
        {
            int x, y;
            double weight;
            edge te = ev.top();
            x=te.u;y=te.v;weight=te.w;
            ev.pop();
            //cout << x  << ' ' << y  << ' ' << weight << endl;
            if (find(x) != find(y))
            {
                uni(x, y);
                if(find(0)==find(N+1)){
                    if(weight==0)cout << "0\n";
                    else {
                        cout.precision(6);
                        cout << fixed << weight/2 << '\n';
                    }
                    break;
                }
            }
        }
        
        
    }
}