#include <iostream>    
#include <queue>

using namespace std;     

vector<pair<int,int>> object_loc, teacher_loc;
int object_size=0;
int N;
char map[6][6];
int dR[4]={0,-1,1,0};
int dC[4]={-1,0,0,1};


bool avoid_teacher() {
    for (auto loc : teacher_loc) {
        int r = loc.first;
        int c = loc.second;
        for (int k=0; k<4; k++) {
            for (int x=1; x<N; x++) {
                int next_r = r+dR[k]*x;
                int next_c = c+dC[k]*x;
                if (0<=next_r && next_r<N && 0<=next_c && next_c<N) {
                    if (map[next_r][next_c]=='S') {
                        return false;
                    } else if (map[next_r][next_c]=='O') {
                        break;
                    } 
                } else {
                    break;
                }
            }
        }
    }
    return true;
}

void pick_loc(int cnt, int object_indx) {
    // cout<<"cnt : "<<cnt<<" object_indx : "<<object_indx <<endl;;
    // for (int i=0; i<N; i++) {
    //     for (int j=0; j<N; j++) {
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    if (cnt==3) {
        if (avoid_teacher()) {
            cout<<"YES"<<endl;
            exit(0); 
        } else {
            return;
        }
    } 

    for (int i=object_indx; i<object_size; i++) {
        // cout << "object_indx ? "<< i <<" object_size ? "<<object_size<<endl;

        map[object_loc[i].first][object_loc[i].second]='O';
        pick_loc(cnt+1, i+1);
        map[object_loc[i].first][object_loc[i].second]='X';
    }
}


int main(void) {
    cin>>N;
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin>>map[i][j];

            if (map[i][j]=='X') {
                object_loc.push_back({i,j});
                object_size+=1;
            } else if (map[i][j]=='T') {
                teacher_loc.push_back({i,j});
            }
        }
    }
    
    pick_loc(0,0);
    cout<<"NO"<<endl;
    return 0;
}