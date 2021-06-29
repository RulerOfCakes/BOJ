#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, M, K;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M >> K;
    if(N<M+K-1||N>M*K){
        cout << -1;
        return 0;
    }
    vector<int> arr(N, 0);
    for(int i = 0; i < N; i++){
        arr[i] = i+1;
    }
    int start= 0;
    for(int i = 1; i <= M; i++){
        int end = min(start+K, N-M+i);
        reverse(arr.begin()+start, arr.begin()+end);
        start=end;
    }
    for(int i = 0; i < N; i++){
        cout << arr[i] << ' ';
    }
}