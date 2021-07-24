#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;
int N, M;
int arr[1000002];  //input heights

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    deque<pi> dq;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        while(!dq.empty()&&dq.front().first<i-2*M+2)dq.pop_front();
        while(!dq.empty()&&dq.back().second<=a)dq.pop_back();
        dq.push_back({i,a});
        if(i>=2*M-2)cout << dq.front().second << ' ';
    }
}