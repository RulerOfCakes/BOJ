#include <bits/stdc++.h>

using namespace std;

int N, M, startp, endp;

int idx[1003];
vector<int> edges[1003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    int a, b, c;
    for(int i = 1; i <= M; i++){
        int t;
        cin >> t;
        b = -1;
        while(t--){
            cin >> a;
            if(b==-1){
                b=a;
                continue;
            }
            edges[b].push_back(a);
            idx[a]++;
            b=a;
        }
    }

    queue<int> q;
    for(int i = 1; i <= N; i++){
        if(!idx[i]){
            q.push(i);
        }
    }
    vector<int> ans;
    while(!q.empty()){
        int curp = q.front();
        ans.push_back(curp);
        q.pop();

        for(auto i : edges[curp]){
            int next = i;
            
            if(!--idx[next]){
                q.push(next);
            }
            
        }
    }
    if(ans.size()<N){
        cout << 0;
        return 0;
    }
    for(int i : ans){
        cout << i << '\n';
    }
}