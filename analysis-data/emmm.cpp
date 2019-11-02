#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("ir-data-26off-2.txt", "r", stdin);
    string line;
    int sp = 0, cnt = 0;
    while(getline(cin, line)) {
        if(line[0] == 's') {
            sscanf(line.c_str(), "space %d", &sp);
            if(sp != 0) {
                cout << (sp > 1000 ? '1' : '0') << (++cnt % 8 == 0 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
