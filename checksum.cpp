#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    if (a.size() != b.size()) {
        cout << "Strings must be same length";
        return 0;
    }

    string sum = "";
    int c = 0;

    for (int i = a.size() - 1; i >= 0; i--) {
        int first = a[i] - '0';
        int second = b[i] - '0';
        int res = first + second + c;

        sum = char((res % 2) + '0') + sum;  
        c = res / 2;  
    }

    cout << sum << endl;

    string checksum = sum;
    for (int i = 0; i < checksum.size(); i++) {
        checksum[i] = (checksum[i] == '0' ? '1' : '0');
    }

    char carryComp = (c == 0 ? '1' : '0');
    checksum = carryComp + checksum;

    cout << checksum << endl;

    return 0;
}
