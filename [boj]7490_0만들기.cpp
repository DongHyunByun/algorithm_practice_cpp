#include <iostream>    
#include <queue>

using namespace std;     

int to_num;

bool is_sum_zero(string str) {
    int total = 0;
    int temp = 1;

    for (int i=2; i<=to_num; i++) {
        if (str[2*i-3]==' ') {
            temp = temp*10 ;
            if (temp>0) {
                temp = temp+i;
            } else {
                temp = temp-i; 
            }
        } else {
            total+=temp;
            temp = 0;

            if (str[2*i-3]=='+') {
                temp = i;
            } else  {
                temp = -1*i;
            }
        }
    }

    total+=temp;
    if (total==0) {
        return true;
    } else {
        return false;
    }
}

void dfs(string str, int now_num) {
    if (now_num==to_num+1) {
        if (is_sum_zero(str)) {
            cout<<str<<endl;
        }
        return;
    }

    string blank_str = str+" "+to_string(now_num);
    dfs(blank_str,now_num+1);

    string plus_str = str+"+"+to_string(now_num);
    dfs(plus_str,now_num+1);

    string minus_str = str+"-"+to_string(now_num);
    dfs(minus_str,now_num+1);
}

int main(void) {
    int T;
    cin>>T;
    for (int t=0; t<T; t++) {
        cin>>to_num;

        dfs("1",2);
        cout<<endl;
    }
}