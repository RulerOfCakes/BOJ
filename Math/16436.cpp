#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ppi = pair<pi, pi>;

int W,H,K;
const int INF = 1e5 + 1;

int arr1[2501][2501];
int arr2[5002][5002];
int sum1[2501][2501];
int sum2[5002][5002];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c, d;
    cin >> W >> H >> K;
	
	for(int i = 0;i  < K; i++){
		cin >> a >> b >> c >> d;
		if(a==1){
            int e;
            cin >> e;
            arr1[b][c]++;
            arr1[b][e+1]--;
            arr1[d+1][c]--;
            arr1[d+1][e+1]++;
        }
        else{
            int x1=b-c-d+2500;
            int y1=b-d+c;
            int x2=b-c+d+2500;
            int y2=b+c+d;
            arr2[x1][y1]++;
            arr2[x1][y2+1]--;
            arr2[x2+1][y1]++;
            arr2[x2+1][y2+1]--;
        }
	}
    sum1[0][0]=arr1[0][0];
	for(int i = 1;i <= 2500;i++){
		sum1[0][i]=arr1[0][i]+sum1[0][i-1];
		sum1[i][0]=arr1[i][0]+sum1[i-1][0];
	}
	for(int i = 1; i <= 2500; i++){
        for(int j = 1;j  <= 2500; j++){
            sum1[i][j]=sum1[i-1][j]+sum1[i][j-1]-sum1[i-1][j-1]+arr1[i][j];
        }
    }

    sum2[0][0]=arr2[0][0];
	for(int i = 1;i <= 5000;i++){
		sum2[0][i]=arr2[0][i]+sum2[0][i-1];
		sum2[i][0]=arr2[i][0]+sum2[i-1][0];
	}
	for(int i = 1; i <= 5000; i++){
        for(int j = 1;j  <= 5000; j++){
            sum2[i][j]=sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1]+arr2[i][j];
        }
    }
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if((sum1[j][i]+sum2[j-i+2500][j+i])%2==0)cout << '.';
            else cout << '#';
            // if(arr1[j][i]%2==0)cout << '.';
            // else cout << '#';
        }
        cout << '\n';
    }
    
}