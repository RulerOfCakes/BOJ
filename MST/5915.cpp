#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;

class edge
{
public:
    int u, v;
    int w;
    edge(int a, int b, int c)
    {
        u = a;
        v = b;
        w = c;
    }
    bool operator<(const edge &e) const
    {
        return w < e.w;
    }
    bool operator>(const edge &e) const
    {
        return w > e.w;
    }
};

int N, M, K;
const int INF = 1e9+7;

int parent[40002];

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

    cin >> N >> M;
    priority_queue<edge, vector<edge>, greater<edge>> ev;

    for (int i = 0; i <= N + 1; i++)
    {
        parent[i] = i;
    }
    for (int i = 1; i <= M; i++)
    {
        int c;
        int f, t;
        cin >> c >> f >> t;
        ev.push(edge(c, f, t));
    }
    ll ans = 0, nums = 1;
    int pw = -1;
    vector<edge> ve;
    set<pi> s;
    while (!ev.empty())
    {
        int x, y;
        int weight;
        edge te = ev.top();
        x = te.u;
        y = te.v;
        weight = te.w;
        ev.pop();
        if (pw != weight)
        {
            // add the edges
            int tmp = 0;
            for (edge e : ve)
            {
                if (find(e.u) != find(e.v))
                {
                    uni(e.u, e.v);
                    ans += e.w;
                    tmp++;
                }
            }
            if (ve.size() == 3)
            {
                if(tmp==1||(s.size()==3&&tmp==2))
                    nums = (nums * 3) % INF;
                //in this case one edge is fixed, you can only choose between the other two
                if(tmp==2&&s.size()==2)
                    nums = (nums * 2) % INF;
            }
            if (ve.size() == 2 && tmp == 1)
                nums = (nums * 2) % INF;
            ve = vector<edge>();
            s=set<pi>();
            pw = weight;
        }
        // cout << x  << ' ' << y  << ' ' << weight << endl;
        int X=find(x),Y=find(y);
        if (X != Y)
        {
            ve.push_back(te);
            s.insert({min(X,Y),max(X,Y)});
            // uni(x, y);
            // ans += weight;
        }
    }
    // last ve
    int tmp = 0;
    for (edge e : ve)
    {
        if (find(e.u) != find(e.v))
        {
            uni(e.u, e.v);
            ans += e.w;
            tmp++;
        }
    }
    if (ve.size() == 3 && ((tmp == 1) || (tmp == 2)))
    {
        nums = (nums * 3) % INF;
        //nums = (nums * 2) % INF;
    }
    if (ve.size() == 2 && tmp == 1)
        nums = (nums * 2) % INF;
    cout << ans << ' ' << nums;
}