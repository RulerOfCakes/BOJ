#include <bits/stdc++.h>


using namespace std;

vector<string> v;
string tmp;
bool cmp1(const string p1, const string p2) {
    return p1 + p2 < p2 + p1;
}

bool cmp2(const string p1, const string p2) {
    return p1 + tmp + p2 < p2 + tmp + p1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    string s;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> s;
        v.push_back(s);
    }
    sort(v.begin(), v.end(), cmp1);
    int i = 0;
    for(i = 0; i < N && v[i][0] == '0'; i++){
        tmp += v[i];
    }
    if(i == N)cout << "INVALID";
    else{
        int first = min_element(v.begin() + i, v.end(), cmp2) - v.begin();
        cout << v[first];
        for(int i = 0; i < N; i++){
            if(i!=first)cout << v[i];
        }
    }
}