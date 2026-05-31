#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int32_t generate_random_int32(mt19937_64& rng) {
    uniform_int_distribution<long long> dist(-2147483648LL, 2147483647LL);
    return static_cast<int32_t>(dist(rng));
}

void generate_int_test(int test_num) {
    int n = 100000;
    cout << n << "\n";
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    if (test_num == 3) {
        uniform_int_distribution<long long> dist_positive(-500000000LL, 2147483647LL);
        for (int i = 0; i < n; ++i) {
            cout << static_cast<int32_t>(dist_positive(rng)) << "\n";
        }
    } else {
        for (int i = 0; i < n; ++i) {
            cout << generate_random_int32(rng) << "\n";
        }
    }
}

void generate_strlexi_test(int test_num) {
    int n = 10000;
    cout << n << "\n";
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < n; ++i) {
        string s(98, 'a');
        s += (char)('a' + rng() % 26);
        s += (char)('a' + rng() % 26);
        cout << s << "\n";
    }
}

void generate_strlenlexi_test(int test_num) {
    int n = 100000;
    cout << n << "\n";
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < n; ++i) {
        char repeated_char = 'a' + (rng() % 26);
        string s(100, repeated_char);
        cout << s << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Sai cú pháp! Định dạng chuẩn: " << argv[0] << " <int/strlexi/strlenlexi> <1/2/3/4/5>\n";
        return 1;
    }

    string benchmark_type = argv[1];
    int test_num = stoi(argv[2]);

    if (test_num < 1 || test_num > 5) {
        cerr << "Số thứ tự bộ test phải nằm trong khoảng từ 1 đến 5.\n";
        return 1;
    }

    if (benchmark_type == "int") {
        generate_int_test(test_num);
    } 
    else if (benchmark_type == "strlexi") {
        generate_strlexi_test(test_num);
    } 
    else if (benchmark_type == "strlenlexi") {
        generate_strlenlexi_test(test_num);
    } 
    else {
        cerr << "Loại dữ liệu không hợp lệ! Vui lòng chọn 'int', 'strlexi', hoặc 'strlenlexi'.\n";
        return 1;
    }

    return 0;
}
