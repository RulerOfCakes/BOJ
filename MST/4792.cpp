#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class edge
{
public:
    int u, v;
    int w;
    edge(int a, int b, int c){
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

int N, M, K;

int parent[1002];

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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while (true)
    {
        cin >> N>>M>>K;
        if(N==0&&M==0&&K==0)break;
        priority_queue<edge,vector<edge>, less<edge>> rv;
        priority_queue<edge,vector<edge>, greater<edge>> bv;
        
        for (int i = 0; i <= N+1; i++)
        {
            parent[i] = i;
        }
        for (int i = 1; i <= M; i++)
        {
            char c;
            int f, t;
            cin >> c >> f >> t;
            if(c=='R'){
                rv.push(edge(f,t,0));
                bv.push(edge(f,t,0));
            }
            else{
                rv.push(edge(f,t,1));
                bv.push(edge(f,t,1));
            }
        }
        int linecnt1=0;
        int ans1=0, ans2=0;
        bool notree=0;
        while (!rv.empty())
        {
            int x, y;
            int weight;
            edge te = rv.top();
            x=te.u;y=te.v;weight=te.w;
            rv.pop();
            //cout << x  << ' ' << y  << ' ' << weight << endl;
            if (find(x) != find(y))
            {
                linecnt1++;
                uni(x, y);
                ans1+=weight;
                if(linecnt1==N-1)break;
                if(linecnt1 > N-1)notree=1;
            }
        }
        if(notree){
            cout << 0 << '\n';
            continue;
        }
        for (int i = 0; i <= N+1; i++)
        {
            parent[i] = i;
        }
        while (!bv.empty())
        {
            int x, y;
            int weight;
            edge te = bv.top();
            x=te.u;y=te.v;weight=te.w;
            bv.pop();
            //cout << x  << ' ' << y  << ' ' << weight << endl;
            if (find(x) != find(y))
            {
                uni(x, y);
                ans2+=weight;
            }
        }
        
        if(min(ans1,ans2) <= K && K <= max(ans1, ans2)){
            cout << 1 << '\n';
        }
        else cout << 0 << '\n';
        
    }
}