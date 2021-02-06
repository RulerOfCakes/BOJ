#include <bits/stdc++.h>

using namespace std;

int T, N;
int homex, homey, endx, endy;
bool verify(int a, int b, int c, int d){
    return abs(c-a) + abs(d-b) <= 1000 ? true : false;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> N;
        vector<bool> visitt(N+1, false);
        int a, b;
        vector<pair<int, int>> v;
        cin >> homex >> homey;
        for(int i = 0; i < N; i++){
            cin >> a >> b;
            v.push_back({a, b});
        }
        cin >> endx >> endy;
        queue<pair<int, int>> q;
        q.push({homex, homey});
        while(!q.empty()){
            int curx = q.front().first, cury = q.front().second;
            q.pop();
            if(verify(curx, cury, endx, endy)){
                visitt[N] = true;
                break;
            }
            for(int i = 0; i < N; i++){
                if(visitt[i])continue;
                if(verify(curx, cury, v[i].first, v[i].second)){
                    visitt[i] = true;
                    q.push(v[i]);
                }
            }
        }
        if(visitt[N]){
            cout << "happy\n";
        }
        else{
            cout << "sad\n";
        }
    }
}