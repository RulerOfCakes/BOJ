
#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

int N, M;
const int INF = 1e9;
int arr[51][51];
vector<pi> chickens,houses;
vector<int> choices;

int calcdist(){
    int ret = 0;
    for(int i = 0; i < houses.size(); i++){
        int cdist = INF;
        for(int nxt : choices){
            cdist=min(cdist, abs(houses[i].first-chickens[nxt].first)+abs(houses[i].second-chickens[nxt].second));
        }
        ret+=cdist;
    }
    return ret;
}

int sol(int cidx, int cnt){
    if(cidx>chickens.size())return INF;
    if(cnt==M){
        return calcdist();
    }
    choices.push_back(cidx);
    int ret = sol(cidx+1,cnt+1);
    choices.pop_back();
    return min(ret,sol(cidx+1,cnt));
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0;j  < N; j++){
            cin >> arr[i][j];
            if(arr[i][j]==1){
                houses.push_back({i,j});
            }
            else if(arr[i][j]==2){
                chickens.push_back({i,j});
            }
        }
    }
    cout << sol(0,0);
}