#include <bits/stdc++.h>
using namespace std;
vector<string> v;
string str1;
string maxx;

bool cmp(const string p1, const string p2) {
    if (p1 == p2) {
        return false;
    }
    if (p1 + p2 < p2 + p1) {
        return false;
    }
    else {
        return true;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, K, x, y = 0, x1 = 0;
    bool notz=0;
    cin >>N;
    for (int i = 0; i < N; i++) {
        cin >> x;
        if(x!=x1)notz=1;
        v.push_back(to_string(x));
        if (x > y) {
            y = x;
        }
    }
    if(!notz){
        cout << 0;
        return 0;
    }
    sort(v.begin(), v.end(), cmp);
    maxx = to_string(y);
    K=N;
    for (int i = 0; i < K; i++) {
        str1 += v[i];
        if (v[i] == maxx && x1 == 0) {
            for (int j = 0; j < N - K; j++) {
                str1 += maxx;
            }
            x1++;
        }
    }
    cout << str1;
}