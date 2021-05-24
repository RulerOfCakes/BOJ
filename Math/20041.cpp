#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int x, y;
    vector<pi> v;
    for(int i = 0; i < N; i++){
        cin >> x >> y;
        v.push_back({x, y});
    }
    int s1, s2;
    cin >> s1 >> s2;
    bool c1=false, c2 = false, c3 = false, c4  =false;
    string ans = "YES";
    int rdiag = s1+s2, ldiag = s1-s2;
    for(int i = 0; i < N; i++){
        int cr = v[i].first+v[i].second;
        int cl = v[i].first-v[i].second;

        if(cr>=rdiag&&cl<=ldiag){
            c1=true;
        }
        if(cr<=rdiag&&cl>=ldiag){
            c2=true;
        }        
        if(cr<=rdiag&&cl<=ldiag){
            c3=true;
        }
        if(cr>=rdiag&&cl>=ldiag){
            c4=true;
        }
    }
    if(c1&&c2&&c3&&c4){
        ans = "NO";
    }
    cout << ans;
}