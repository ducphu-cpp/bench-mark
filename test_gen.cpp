#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int RandInt(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

char RandChar() {
    return 'a' + RandInt(0, 25);
}


void genInt(int testid) {

    int n;

    if (testid == 1) n = 1000;
    else if (testid == 2) n = 5000;
    else if (testid == 3) n = 20000;
    else if (testid == 4) n = 50000;
    else n = 100000;

    cout << n << '\n';

    for (int i = 0; i < n; i++) {
        cout << RandInt(INT_MIN, INT_MAX) << '\n';
    }
}


void genStrLexi(int testid) {

    int n;

    if (testid == 1) n = 1000;
    else if (testid == 2) n = 5000;
    else if (testid == 3) n = 20000;
    else if (testid == 4) n = 50000;
    else n = 100000;

    cout << n << '\n';

    for (int i = 0; i < n; i++) {

        int len = RandInt(80, 120);

        char c = RandChar();

        string s(len, c);

        s[len - 1] = RandChar();

        cout << s << '\n';
    }
}

void genStrLenLexi(int testid) {

    int n;

    if (testid == 1) n = 1000;
    else if (testid == 2) n = 5000;
    else if (testid == 3) n = 20000;
    else if (testid == 4) n = 50000;
    else n = 100000;

    cout << n << '\n';

    for (int i = 0; i < n; i++) {

        int len = RandInt(90, 100);

        string s(len, 'a');

        int changes = RandInt(1, 3);

        for (int j = 0; j < changes; j++) {

            int pos = RandInt(len - 5, len - 1);

            s[pos] = RandChar();
        }

        cout << s << '\n';
    }
}

// ====================== MAIN ======================

int main(int argc, char* argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc != 3) {
        return 0;
    }

    string type = argv[1];
    int testid = stoi(argv[2]);

    if (testid < 1 || testid > 5) {
        return 0;
    }

    if (type == "int") {
        genInt(testid);
    }
    else if (type == "strlexi") {
        genStrLexi(testid);
    }
    else if (type == "strlenlexi") {
        genStrLenLexi(testid);
    }

    return 0;
}
