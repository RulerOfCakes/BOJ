#include <bits/stdc++.h>

using namespace std;

vector<int> v;
int ans = 0;
int arr[10][10];
set<int> boxes[9];
set<int> row[9],col[9];
bool done = 0;

int boxidx(int x){
    return (x/27)*3+(x%9)/3;
}

void Backtracking(int cx){
    if(done)return;
    if(cx>=80){done=1;return;}
    //cout << cx << endl;
    int nx = (cx+1)/9, ny = (cx+1)%9, bidx = boxidx(cx+1);
    if(arr[nx][ny]!=0)Backtracking(cx+1);
    else{
        for(int i = 1; i <= 9; i++){
            if(boxes[bidx].count(i)||row[nx].count(i)||col[ny].count(i))continue;
            arr[nx][ny]=i;
            boxes[bidx].insert(i);
            row[nx].insert(i);
            col[ny].insert(i);
            Backtracking(cx+1);
            if(done)return;
            
            arr[nx][ny]=0;
            boxes[bidx].erase(i);
            row[nx].erase(i);
            col[ny].erase(i);
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for(int i = 0; i < 9; i++){
        boxes[i]=set<int>();
        row[i]=set<int>();
        col[i]=set<int>();
    }
    for(int i = 0; i < 9; i++){
        string s;
        cin >> s;
        for(int j = 0; j < 9; j++){
            arr[i][j]=s[j]-'0';
            if(arr[i][j]){
                int bidx = 3*(i/3)+j/3;
                row[i].insert(arr[i][j]);
                col[j].insert(arr[i][j]);
                boxes[bidx].insert(arr[i][j]);
            }
        }
    }
    
    Backtracking(-1);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout << arr[i][j];
        }
        cout << '\n';
    }
    
}