#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<ll, ll>;
int ccw(pi p1, pi p2, pi p3){
    ll sol = (p1.first*p2.second + p2.first*p3.second + p3.first*p1.second) - (p1.second*p2.first + p2.second*p3.first + p3.second*p1.first);
    if(sol<0)return -1;
    else if(sol == 0)return 0;
    else return 1;
}
int intersection(pi p1, pi p2, pi p3, pi p4){
    int first = ccw(p1, p2, p3), second = ccw(p1, p2, p4);
    int third = ccw(p3, p4, p1), fourth = ccw(p3, p4, p2);
    int check1 = first*second, check2 = third*fourth;
    if(check1==0&&check2==0){
        return min(p3, p4)<=max(p1, p2) && min(p1, p2) <= max(p3, p4);
    }
    return check1 <=0 && check2 <= 0;
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    pi p1, p2, p3, p4;
    cin >> p1.first >> p1.second >> p2.first >> p2.second >> p3.first >> p3.second >> p4.first >> p4.second;
    
    cout << intersection(p1, p2, p3, p4);
}