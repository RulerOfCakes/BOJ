#include <bits/stdc++.h>

using namespace std;

int N;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int a;
    priority_queue<int> maxx;
    priority_queue<int, vector<int>, greater<int>> minn;
    for(int i = 0; i < N; i++){
        cin >> a;
        if(maxx.size() <= minn.size()){
            maxx.push(a);
        } else {
            minn.push(a);
        }
        if(minn.empty()){
            cout << maxx.top() << '\n';
            continue;
        }
        if(maxx.top() > minn.top()){
            int maxxt = maxx.top(), minnt = minn.top();
            maxx.pop(); minn.pop();
            maxx.push(minnt); minn.push(maxxt);
        }
        cout << maxx.top() << '\n';
    }

    
}