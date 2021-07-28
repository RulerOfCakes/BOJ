#include <bits/stdc++.h>

using namespace std;

using pd = pair<double,double>;

int N, T;
double arrx[1002],arry[1002];
double pdist(pd p1, pd p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    double tX=0,tY=0;
    for(int i = 0; i < N; i++){
        
        cin >> arrx[i] >> arry[i];
        tX+=arrx[i];tY+=arry[i];
    }
    //middle point of all points
    tX/=N;tY/=N;
    //p = gradient, dist = actual radius of minimum enclosing circle
    double p=0.1,dist,tempdist;
    for(int i = 0; i < 30000; i++){
        int idx=0;
        dist=pdist({tX,tY},{arrx[0],arry[0]});
        for(int j = 1; j < N; j++){
            tempdist=pdist({tX,tY},{arrx[j],arry[j]});
            if(dist<tempdist){
                dist=tempdist;
                idx=j;
            }
        }
        //moving the center points slightly towards the furthest point
        tX+=(arrx[idx]-tX)*p;
        tY+=(arry[idx]-tY)*p;
        p*=0.999;
    }
    cout<<fixed;cout.precision(3);
    cout << tX << ' ' << tY << '\n';
    cout << sqrt(dist);
}