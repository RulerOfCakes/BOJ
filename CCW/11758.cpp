#include <bits/stdc++.h>

using namespace std;

using pi = pair<int, int>;
int ccw(pi p1, pi p2, pi p3){
    int sol = (p1.first*p2.second + p2.first*p3.second + p3.first*p1.second) - (p1.second*p2.first + p2.second*p3.first + p3.second*p1.first);
    if(sol<0)return -1;
    else if(sol == 0)return 0;
    else return 1;
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    pi p1, p2, p3;
    cin >> p1.first >> p1.second >> p2.first >> p2.second >> p3.first >> p3.second;
    cout << ccw(p1, p2, p3);
}