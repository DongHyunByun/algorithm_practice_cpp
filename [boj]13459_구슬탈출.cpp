#include <iostream>
#include <queue>
#include <set>

using namespace std;

char my_map[10][10];
int N,M;
int dR[4] = {-1,0,1,0};
int dC[4] = {0,1,0,-1};

pair<int,int> tilt(int r, int c, int tilt_side) {
    while(true) {
        int next_r = r+dR[tilt_side];
        int next_c = c+dC[tilt_side];

        // cout<<"next loc"<<next_r<<" "<<next_c<<" "<<map[next_r][next_c]<<endl;

        if (0<=next_r && next_r<N && 0<=next_c && next_c<M) {
            if (my_map[next_r][next_c]=='#') {
                return {r,c};
            } else if (my_map[next_r][next_c]=='B' || my_map[next_r][next_c]=='R') {
                return {r,c};
            } else if (my_map[next_r][next_c]=='O') {
                return {next_r,next_c};
            } 
            else {
                r = next_r;
                c = next_c;
                cout<<r<<" "<<c<<endl;
            }
        } else {
            return {r,c};
        }
    }
}

int to_num_key(pair<int,int> red_loc, pair<int,int> blue_loc) {
    int a = red_loc.first*1000;
    int b = red_loc.second*100;
    int c = blue_loc.first*10;
    int d = blue_loc.second*1;
    
    return a+b+c+d;
}

int *key_to_loc(int key) {
    int static arr[4];

    for (int k=3; k>=0; k--) {
        arr[k]=key%10;
        key = key/10;
    }

    return arr;
}

int main(void) {
    // 입력값
    cin>>N>>M;
    pair<int,int> red_loc;
    pair<int,int> blue_loc;

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin>>my_map[i][j];


            if (my_map[i][j]=='R') {
                red_loc = {i,j};
            }
            if (my_map[i][j]=='B') {
                blue_loc = {i,j};
            }
        }
    }

    // 기울이기
    int init_key = to_num_key(red_loc, blue_loc);

    queue<int> q;
    set<int> visited;

    q.push(init_key);
    visited.insert(init_key);


    while (!q.empty()) {
        int now_key = q.front(); q.pop();
        int *now_arr;
        now_arr = key_to_loc(now_key);

        int red_r = *(now_arr);
        int red_c = *(now_arr+1);
        int blue_r = *(now_arr+2);
        int blue_c = *(now_arr+3);

        cout<<red_r<<","<<red_c<<" "<<blue_r<<blue_c<<endl;
        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                cout<<my_map[i][j]<<" ";
            }
            cout<<endl;
        }


        for (int k=0; k<4; k++) {
            pair<int,int> next_red_loc;
            pair<int,int> next_blue_loc;

            //파란색이 먼저 가야되는 경우
            if ( (k==0 && red_c==blue_c && red_r>blue_r)||(k==1 && red_r==blue_r && red_c<blue_c)||(k==3 && red_c==blue_c && red_r<blue_r)||(k==3 && red_r==blue_r && red_c>blue_c)) {
                my_map[blue_r][blue_c]='.';
                next_blue_loc = tilt(blue_r, blue_c, k);
                int next_blue_r = next_blue_loc.first;
                int next_blue_c = next_blue_loc.second;

                if (my_map[next_blue_r][next_blue_c]=='O') {
                    my_map[blue_r][blue_c]='B';
                    continue;
                } else {
                    my_map[next_blue_r][next_blue_c]='B';
                }

                my_map[red_r][red_c]='.';
                next_red_loc = tilt(red_r, red_c, k);
                int next_red_r = next_red_loc.first;
                int next_red_c = next_red_loc.second;

                if (my_map[next_red_r][next_red_c]=='O') {
                    cout<<1<<endl;
                    return 0;
                } else {
                    my_map[next_red_r][next_red_c]='R';
                }

            } else { //빨간색이 먼저 가야되는 경우
                bool red_drop=false;

                my_map[red_r][red_c]='.';
                next_red_loc = tilt(red_r, red_c, k);
                int next_red_r = next_red_loc.first;
                int next_red_c = next_red_loc.second;

                if (my_map[next_red_r][next_red_c]=='O') {
                    my_map[red_r][red_c]='R';
                    red_drop = true;
                } else {
                    my_map[next_red_r][next_red_c]='R';
                }

                my_map[blue_r][blue_c]='.';
                next_blue_loc = tilt(blue_r, blue_c, k);
                int next_blue_r = next_blue_loc.first;
                int next_blue_c = next_blue_loc.second;

                if (my_map[next_blue_r][next_blue_c]=='O') {
                    my_map[blue_r][blue_c]='B';
                    continue;
                } else {
                    if (red_drop) {
                        cout<<1<<endl;
                        return 0;
                    } else {
                        my_map[next_blue_r][next_blue_c]='B';
                    }
                }    
            }

            int now_num_key = to_num_key(next_red_loc, next_blue_loc);

            if (visited.find(now_num_key)==visited.end()) {
                q.push(now_num_key);
                visited.insert(now_num_key);
            }

        }
    }

    return 0;

}