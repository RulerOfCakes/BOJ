#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N;
const int INF = 1e9+7;
int hap[1000002], str[1000002];
pi young[1000002], old[1000002];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    young[0]={INF,0};
    old[N+1]={0,INF};
    for(int i = 1; i <= N; i++){
        cin >> hap[i] >> str[i];
        int minh = young[i-1].first, maxs = young[i-1].second;
        int first = min(minh,hap[i]), second = max(maxs,str[i]);
        if(hap[i]==0)first=minh;
        if(str[i]==0)second=maxs;
        young[i]={first,second};
    }
    for(int i = N; i >= 1; i--){
        int maxh = old[i+1].first, mins = old[i+1].second;
        int first=max(maxh,hap[i]),second=min(mins,str[i]);
        if(hap[i]==0)first=maxh;
        if(str[i]==0)second=mins;
        old[i]={first,second};
    }
    for(int i = N-1; i >= 1; i--){
        if(young[i].first > old[i+1].first){
            if(young[i].second < old[i+1].second){
                cout << i;
                return 0;
            }
        }
    }
    cout << -1;
}