#include <iostream>
#include <algorithm>

using namespace std;


int main(void) {
    string cent;
    getline(cin, cent);
    int size = cent.length();

    bool is_tag = false;
    string ans;
    string now_word;

    for (int i=0; i<size; i++) {
        // in tag
        if (is_tag) {
            ans+=cent[i];

            if (cent[i]=='>') {
                is_tag=false;
            }
        } else { //out tag
            if (cent[i]=='<') {
                if (!now_word.empty()) {
                    reverse(now_word.begin(),now_word.end());
                    ans+=now_word;
                    now_word="";
                }
                is_tag=true;
                ans+=cent[i];
            } else if (cent[i]==' ') {
                reverse(now_word.begin(),now_word.end());
                ans+=now_word;
                now_word="";

                ans+=cent[i];
            } else {
                now_word+=cent[i];
            }
        }
    }
    if (!now_word.empty()) {
        reverse(now_word.begin(),now_word.end());
        ans+=now_word;
    }

    cout<<ans<<endl;
    return 0;
}