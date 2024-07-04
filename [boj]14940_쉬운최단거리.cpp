#include <iostream>    
#include <queue>

using namespace std;     
 
int m,n;
int dR[4] = {0,0,-1,1};
int dC[4] = {1,-1,0,0};


int main(void)           
{
    cin >> n;
    cin >> m;

    int visited[n][m];
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            visited[i][j]=-1;
        }
    }

    int arr[n][m];
    int start_r, start_c;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int a;
            cin >> a;
            if (a==2) {
                start_r = i;
                start_c = j;
            } else if (a==0){
                visited[i][j]=0;
            }
            arr[i][j] = a;
        }
    }
    
    queue<vector<int>> q;
    visited[start_r][start_c]=0;
    q.push({start_r,start_c});

    while(!q.empty()) {
        vector<int> loc = q.front(); 
        q.pop();
        int r = loc[0];
        int c = loc[1];
        int now_dist = visited[r][c];

        for (int k=0; k<4; k++) {
            int next_r = r+dR[k];
            int next_c = c+dC[k];
        
            if (0<=next_r && next_r<n && 0<=next_c && next_c<m) {
                if (visited[next_r][next_c]==-1) {
                
                    visited[next_r][next_c] = now_dist+1;
                    q.push({next_r,next_c});
                    
                }   
            }
        }
    }   
        
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout << visited[i][j] <<" ";
        }
        cout<<endl;
    }
    

    return 0; // 프로그램 끝
}
