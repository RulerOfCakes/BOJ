#include <bits/stdc++.h>

using namespace std;

using pi = pair<long long, long long>;

int N;
vector<pi> v;

double ccw(pi p1, pi p2, pi p3){
    double sol = (p1.first*p2.second + p2.first*p3.second + p3.first*p1.second) - (p1.second*p2.first + p2.second*p3.first + p3.second*p1.first);
    return sol;
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        pi temp;
        cin >> temp.first >> temp.second;
        v.push_back(temp);
    }
    double ans = 0;
    for(int i = 2; i < N; i++){
        pi cur1 = v[i-1], cur2 = v[i];
        ans += ccw(v[0], cur1, cur2);
    }
    printf("%.1lf", abs(ans)/2);
}