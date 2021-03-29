#include <bits/stdc++.h>

using namespace std;
int N, S;
vector<int> v;
int ans = 0;
bool visited[22];

void Backtracking(int n, int cur){
    if(n == N){
        bool checked = 0;
        for(int i = 0; i < v.size(); i++){
            if(visited[i])checked=1;
        }
        if(!checked)return;
        if(cur!=S) return;
        else ans++;
        return;
    }
    visited[n] = 1;
    Backtracking(n+1, cur+v[n]);
    visited[n] = 0;
    Backtracking(n+1, cur);
    return;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> S;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    Backtracking(0, 0);

    cout << ans;
    
}