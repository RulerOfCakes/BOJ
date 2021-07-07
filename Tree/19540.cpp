#include <bits/stdc++.h>
//source : https://blog.kakaocdn.net/dn/cCNqTS/btqF1A8EW6k/QdZPKY0KXICKklcV0wOXd1/img.png
using namespace std;
using ll = long long;
using pi = pair<int, int>;

int N;
const int INF = 1e4 + 4;

vector<vector<int>> v;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c, d;

    cin >> N;
    v=vector<vector<int>>(N+1,vector<int>());
    if (N < 9)
    {
        v[1].push_back(2);
        v[2].push_back(3);
        v[3].push_back(4);
        v[4].push_back(5);
        v[2].push_back(6);
        if(N>6){
            v[3].push_back(7);
            if(N>7){
                v[3].pop_back();
                v[6].push_back(7);
                v[4].push_back(8);
            }
        }
    }
    else
    {
        v[1].push_back(2);
        v[2].push_back(3);
        v[3].push_back(4);
        v[3].push_back(6);
        v[4].push_back(5);
        v[6].push_back(7);
        v[3].push_back(8);
        v[8].push_back(9);
        
        int llimit = ((N % 6) >= 3) ? ((N - (N % 6)) + 3) : (N - (N % 6) - 3);
        for (int i = 9; i < llimit; i+=6)
        {
            v[i].push_back(i+1);
            v[i+1].push_back(i+2);
            v[i].push_back(i+3);
            v[i+3].push_back(i+4);
            v[i].push_back(i+5);
            v[i+5].push_back(i+6);
        }
        int rest = N-llimit;
        if(rest<5){
            if(rest>0){
                v[2].push_back(llimit+1);
                if(rest>1){
                    v[4].push_back(llimit+2);
                    if(rest>2){
                        v[6].push_back(llimit+3);
                        if(rest>3){
                            v[llimit-1].push_back(llimit+4);
                        }
                    }
                }
            }
        }
        else if(rest==5){
            v[1].push_back(llimit+1);
            v[1].push_back(llimit+2);
            v[llimit+2].push_back(llimit+3);
            v[llimit+3].push_back(llimit+4);
            v[llimit+3].push_back(llimit+5);
        }
    }

    for(int i = 1; i <= N; i++){
        if(v[i].empty())continue;
        for(int j = 0; j < v[i].size(); j++){
            cout << i << ' ' << v[i][j] << '\n';
        }
    }
}