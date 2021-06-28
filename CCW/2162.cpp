#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<int, int>;

int N;
vector<pair<pi, pi>> v;
int parent[3002];
int cnt[3002];

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
    parent[ar]=br;
}
int ccw(pi p1, pi p2, pi p3){
    ll sol = (p1.first*p2.second + p2.first*p3.second + p3.first*p1.second) - (p1.second*p2.first + p2.second*p3.first + p3.second*p1.first);
    if(sol<0)return -1;
    else if(sol == 0)return 0;
    else return 1;
}
int intersection(pi p1, pi p2, pi p3, pi p4){
    int first = ccw(p1, p2, p3), second = ccw(p1, p2, p4);
    int third = ccw(p3, p4, p1), fourth = ccw(p3, p4, p2);
    int check1 = first*second, check2 = third*fourth;
    if(check1==0&&check2==0){
        return min(p3, p4)<=max(p1, p2) && min(p1, p2) <= max(p3, p4);
    }
    return check1 <=0 && check2 <= 0;
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    for(int i = 0; i <= N; i++){
        cnt[i] = 0;
        parent[i] = i;
    }
    v.push_back({{0,0},{0,0}});
    for(int i = 0; i < N; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        v.push_back({{a, b}, {c, d}});
    }
    for(int i = 1; i < N; i++){
        for(int j = i+1; j <= N; j++){
            if(intersection(v[i].first, v[i].second, v[j].first, v[j].second)){
                uni(i, j);
            }
        }
    }
    for(int i = 1; i <= N; i++){
        cnt[find(i)]++;
    }
    int groupcnt=0, groupnum=0;
    for(int i = 1; i<= N; i++){
        if(cnt[i])groupcnt++;
        groupnum=max(groupnum, cnt[i]);
    }
    cout << groupcnt << '\n' << groupnum;
}