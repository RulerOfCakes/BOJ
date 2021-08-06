#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M;

int parent[52];


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
    vector<vector<int>> parties;
    for (int i = 0; i <= N; i++)
    {
        parent[i] = i;
    }
    int knowns;
    cin >> knowns;
    set<int> illuminati;
    int prev=-1;
    for (int i = 0; i < knowns; i++)
    {
        int a;
        cin >> a;
        illuminati.insert(a);
        if(i>0){
            uni(prev,a);
        }
        prev=a;
    }
    for (int i = 0; i < M; i++)
    {
        int a;
        cin >> a;
        vector<int> tmpv(a);
        for (int i = 0; i < a; i++)
        {
            
            cin >> tmpv[i];
            if(i>0){
                uni(tmpv[i-1],tmpv[i]);
            }
        }
        parties.push_back(tmpv);
    }
    int ans = 0;
    int par = find(*illuminati.begin());
    for(int i = 0; i < M; i++){
        bool TRUTH = 0;
        for(int j = 0; j < parties[i].size(); j++){
            if(find(parties[i][j])==par)TRUTH=1;
        }
        if(!TRUTH)ans++;
    }
    cout << ans;
}