#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<ll, ll>;

int T;

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
    pi p1, p2, plt, prb;
    cin >> T;
    while(T--){
        cin >> p1.first >> p1.second >> p2.first >> p2.second;
        cin >> plt.first >> plt.second >> prb.first >> prb.second;
        pi plb = {plt.first, prb.second}, prt = {prb.first, plt.second};
        bool fact = 0;
        if((p1.first>=min(plt.first, prt.first)&&p1.first<=max(plt.first,prt.first))&&
            (p1.second>=min(plt.second, plb.second)&&p1.second<=max(plt.second, plb.second))&&
            (p2.first>=min(plt.first, prt.first)&&p2.first<=max(plt.first,prt.first))&&
            (p2.second>=min(plt.second, plb.second)&&p2.second<=max(plt.second, plb.second))){
                fact=1;
            }
        if(intersection(p1, p2, plt, plb)||
            intersection(p1, p2, plt, prt) ||
            intersection(p1, p2, prt, prb) ||
            intersection(p1, p2, plb, prb)){
            fact=1;
        }

        if(fact){
            cout << 'T' << '\n';
        }
        else{
            cout << 'F' << '\n';
        }
    }
}