#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pi = pair<ll, ll>;

const double MIN = 1e-10;

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

pair<double,double> intpoint(double s1, double s2, pi p1, pi p2, pi p3, pi p4){
    double x,y;
    x = (s1*p1.first-s2*p3.first+p3.second-p1.second)/(s1-s2);
    y = s1*x-s1*p1.first+p1.second;
    return {x,y};
}

double dist(pi p1, pi p2){
    return sqrt((double)(p1.first-p2.first)*(p1.first-p2.first) + (double)(p1.second-p2.second)*(p1.second-p2.second));
}

bool slopecheck(pi p1, pi p2, pi p3, pi p4){
    //p1==p3
    if(p1.first==p2.first){
        if(p3.first==p4.first){
            ll d1 = p2.second-p1.second, d2 = p4.second-p1.second;
            if((abs(d1+d2)>abs(-d1+d2))||abs(d1)==abs(d2)){
                return 1;
            }
            return 0;
        }
    }
    else
    {
        double s1 = (double)(p1.second-p2.second)/(p1.first-p2.first),
        s2 = (double)(p3.second-p4.second)/(p3.first-p4.first);
        if(abs(s1-s2)<MIN){
            double fd = dist(p2,p4);
            double d1 = dist(p1,p2),d2=dist(p1,p4);
            if(abs(fd-(d1+d2))<MIN){
                return 1;
            }
            else{
                //cout << "WRONG";
                return 0;
            }
        }
    }
    
    return 1;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    pi p1, p2, p3, p4;
    cin >> p1.first >> p1.second >> p2.first >> p2.second >> p3.first >> p3.second >> p4.first >> p4.second;
    int ans = intersection(p1,p2,p3,p4);
    cout << ans << '\n';
    if(ans){
        double x,y;
        if(p1==p3){
            if(p2==p4)return 0;
            if(!slopecheck(p1,p2,p3,p4))return 0;
            cout << p1.first << ' ' << p1.second;
        }
        else if(p1==p4){
            if(p2==p3) return 0;
            if(!slopecheck(p1,p2,p4,p3))return 0;

            cout << p1.first << ' ' << p1.second;
        }
        else if(p2==p3){
            if(p1==p4)return 0;
            if(!slopecheck(p2,p1,p3,p4))return 0;

            cout << p2.first << ' ' << p2.second;
        }
        else if(p2==p4){
            if(p1==p3)return 0;
            if(!slopecheck(p2,p1,p4,p3))return 0;
            
            cout << p2.first << ' ' << p2.second;
        }
        else{
            //if parallel to y axis
            //y=ax-ax1+y1
            //x=(y+ax1-y1)/a
            if(p1.first==p2.first){
                if(p3.first!=p4.first){
                    double a = (double)(p3.second-p4.second)/(p3.first-p4.first);
                    x=p1.first;
                    y=a*x-a*p3.first+p3.second;
                }
            }
            else if(p3.first==p4.first){
                double a = (double)(p1.second-p2.second)/(p1.first-p2.first);
                x=p3.first;
                y=a*x-a*p1.first+p1.second;
            }
            else{
                double s1 = (double)(p1.second-p2.second)/(p1.first-p2.first),
                s2 = (double)(p3.second-p4.second)/(p3.first-p4.first);
                if(abs(s1-s2)<MIN){
                    return 0;
                }
                tie(x,y) = intpoint(s1,s2,p1,p2,p3,p4);
            }
            cout.precision(10);
            cout << x << ' ' << y;
        }
    }
    
}