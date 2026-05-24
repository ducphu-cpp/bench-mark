#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int RandInt(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

char RandChar() {
    return 'a' + RandInt(0, 25);
}

string RandomString(int len) {
    string s;
    s.reserve(len);

    for (int i = 0; i < len; i++)
        s += RandChar();

    return s;
}


void genIntTest(string filename) {
    ofstream out(filename);

    int n = 100000;
    out << n << '\n';

    for (int i = 0; i < n; i++) {
        out << RandInt(INT_MIN, INT_MAX) << '\n';
    }
}

void genStrLenLexi(string filename) {
    ofstream out(filename);

    int n = 10000;
    out << n << '\n';

    for (int i = 0; i < n; i++) {

        int len = RandInt(80, 100);

        string s(len, 'a');

        int changes = RandInt(1, 3);

        for (int j = 0; j < changes; j++) {
            int pos = RandInt(len - 5, len - 1);
            s[pos] = RandChar();
        }

        out << s << '\n';
    }
}


void genStrLexi(string filename) {
    ofstream out(filename);

    int n = 100000;
    out << n << '\n';

    for (int i = 0; i < n; i++) {

        int len = RandInt(90, 110);

        char base = RandChar();

        string s(len, base);

        s[len - 1] = RandChar();

        out << s << '\n';
    }
}

int main() {

    system("mkdir int");
    system("mkdir strlenlexi");
    system("mkdir strlexi");

    for (int i = 1; i <= 5; i++) {

        string id = (i < 10 ? "00" : "0") + to_string(i);

        genIntTest("int/test" + id + ".in");

        genStrLenLexi("strlenlexi/test" + id + ".in");

        genStrLexi("strlexi/test" + id + ".in");
    }

    return 0;
}
