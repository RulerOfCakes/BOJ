
#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

const int MAXPARENT = 18;
const int INF = 1e9;
int N, M;
int parent[100002][18],lmin[101010][18],lmax[101010][18];
int depth[100002];
int length[100002];
vector<vector<pi>> v;

//initializing base parent and depths
void initTree(int x)
{
    for (pi next : v[x])
    {
        if (depth[next.first] == -1)
        {
            parent[next.first][0] = x;
            lmin[next.first][0]=next.second;
            lmax[next.first][0]=next.second;
            depth[next.first] = depth[x] + 1;
            length[next.first] = length[x] + next.second;
            initTree(next.first);
        }
    }
}

void initLCA(){
    for(int j = 1; j < MAXPARENT; j++){
        for(int i = 1; i <= N; i++){
            parent[i][j]=parent[parent[i][j-1]][j-1];
            lmin[i][j]=min(lmin[i][j-1],lmin[parent[i][j-1]][j-1]);
            lmax[i][j]=max(lmax[i][j-1],lmax[parent[i][j-1]][j-1]);
        }
    }
}

pi lca(int a, int b)
{
    int tmin=INF,tmax=-INF;
    if (depth[a] < depth[b])
        swap(a, b);
    int diff = depth[a] - depth[b];
    //getting rid of depth diff
    for (int j = 0; diff; j++)
    {
        if (diff % 2){
            tmin=min(tmin,lmin[a][j]);
            tmax=max(tmax,lmax[a][j]);
            a = parent[a][j];
        }
        diff /= 2;
    }

    if (a != b)
    {
        for (int j = MAXPARENT - 1; j >= 0; j--)
        {
            if (parent[a][j] != 0 && parent[a][j] != parent[b][j])
            {
                tmin=min(tmin,min(lmin[a][j],lmin[b][j]));
                tmax=max(tmax,max(lmax[a][j],lmax[b][j]));
                a = parent[a][j];
                b = parent[b][j];
            }
        }
        tmin=min(tmin,min(lmin[a][0],lmin[b][0]));
        tmax=max(tmax,max(lmax[a][0],lmax[b][0]));
    }
    return {tmin,tmax};
} 

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    v = vector<vector<pi>>(N + 1, vector<pi>());
    for (int i = 0; i < N - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
    }

    fill(depth, depth + N + 1, -1);
    fill(length, length + N + 1, -1);
    depth[1] = 0;
    length[1] = 0;
    lmin[1][0]=INF;
    initTree(1);
    initLCA();

    cin >> M;

    for (int i = 0; i < M; i++)
    {
        int a,b;
        cin >> a >> b;
        auto tmp = lca(a,b);
        cout << tmp.first << ' ' << tmp.second << '\n';
    }
}