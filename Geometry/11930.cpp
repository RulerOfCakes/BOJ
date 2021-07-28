#include <bits/stdc++.h>

using namespace std;

int N;
double arrx[1002],arry[1002],arrz[1002];
double pdist(double x, double y, double z)
{
    return x*x+y*y+z*z;
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    double tX=0,tY=0,tZ=0;
    for(int i = 0; i < N; i++){
        
        cin >> arrx[i] >> arry[i] >> arrz[i];
        tX+=arrx[i];tY+=arry[i];tZ+=arrz[i];
    }
    //middle point of all points
    tX/=N;tY/=N;tZ/=N;
    //p = gradient, dist = actual radius of minimum enclosing circle
    double p=0.1,dist,tempdist;
    for(int i = 0; i < 30000; i++){
        int idx=0;
        dist=pdist(tX-arrx[0],tY-arry[0],tZ-arrz[0]);
        for(int j = 1; j < N; j++){
            tempdist=pdist(tX-arrx[j],tY-arry[j],tZ-arrz[j]);
            if(dist<tempdist){
                dist=tempdist;
                idx=j;
            }
        }
        //moving the center points slightly towards the furthest point
        tX+=(arrx[idx]-tX)*p;
        tY+=(arry[idx]-tY)*p;
        tZ+=(arrz[idx]-tZ)*p;
        p*=0.999;
    }
    cout<<fixed;cout.precision(2);
    
    cout << sqrt(dist);
}