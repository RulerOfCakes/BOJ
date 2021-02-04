#include <bits/stdc++.h>

using namespace std;

int arr[3];
bool visit[202][202];
queue<pair<int, int>> q;
priority_queue<int> pq;
void verify(int a, int b){
    if(!visit[a][b]){
        visit[a][b] = 1;
        q.push({a, b});
    }
}
void bfs(){
    
    q.push({0, 0});
    visit[0][0] = 1;
    while(!q.empty()){
        int a = q.front().first, b = q.front().second, c = arr[2]-a-b;
        q.pop();
        if(!a)pq.push(-c);

        int move = min(a, arr[1]-b);
        verify(a-move, b+move);
        move = min(a, arr[2]-c);
        verify(a-move, b);
        move = min(b, arr[0]-a);
        verify(a+move, b-move);
        move = min(b, arr[2]-c);
        verify(a, b-move);
        move = min(c, arr[0]-a);
        verify(a+move, b);
        move = min(c, arr[1]-b);
        verify(a, b+move);
    }
}

int main(){
    cin >> arr[0] >> arr[1] >> arr[2];
    bfs();
    while(!pq.empty()){
        cout << -pq.top() << " ";
        pq.pop();
    }
}