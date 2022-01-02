#include <bits/stdc++.h>

using namespace std;
using ll = long long;


double dist(double x, double y, double z, double c){
    return (x-z)*(x-z)+(y-c)*(y-c);
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(0);
    double x1,x2,y1,y2;
    double dx,dy;
    cin>>x1>>y1;
    cin>>x2>>y2>>dx>>dy;
    double s=0, e = 100000;

    while(s+0.00003<=e){
        double l = (2*s+e)/3,r=(s+2*e)/3;
        int t1=x2+(dx*l), t2=y2+(dy*l), t3=x2+(dx*r), t4=y2+(dy*r);
        if(dist(t1,t2,x1,y1)>dist(t3,t4,x1,y1))s=l;
        else e=r;
    }
    cout << floor(x2+(dx*s)+0.5) << ' ' << floor(y2+(dy*s)+0.5);
}