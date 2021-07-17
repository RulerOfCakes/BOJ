#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 100002;
int N, M;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> N >> M;
    vector<vector<int>> meetings;

    for (int i = 0; i < M; i++)
    {
        int k;
        cin >> k;
        vector<int> tv(k);

        for (int j = 0; j < k; j++)
        {
            cin >> tv[j];
        }

        meetings.push_back(tv);
    }
    vector<int> infectedfinal(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> infectedfinal[i];
    }

    vector<int> ans(infectedfinal.begin(), infectedfinal.end());
    
    for (int i = M-1; i >= 0; i--)
    {
        bool falsened = 0;
        for (int j = 0; j < meetings[i].size(); j++)
        {
            if (!ans[meetings[i][j]]){
                falsened = 1;
            }
        }
        if (!falsened){
            
            continue;
        }
        for (int j = 0; j < meetings[i].size(); j++)
        {
            ans[meetings[i][j]] = 0;
        }
    }
    bool anscheck=1;
    vector<int> newans(ans.begin(),ans.end());
    for(int i = 0; i < M; i++){
        bool go =0;
        for(int j = 0; j < meetings[i].size(); j++){
            if(newans[meetings[i][j]]){
                go=1;
            }
        }
        if(go){
            for(int j = 0; j < meetings[i].size(); j++){
                newans[meetings[i][j]]=1;
            }
        }
    }
    for(int i = 1; i <= N; i++){
        if(newans[i]!=infectedfinal[i])anscheck=0;
    }

    if(!anscheck){
        cout << "NO" << '\n';
        return 0;
    }
    
    cout << "YES" << '\n';
    for (int i = 1; i <= N; i++)
    {
        cout << ans[i] << ' ';
    }
}