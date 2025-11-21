#include <iostream>
using namespace std;

int main() {
    string data;
    cout << "Enter the bit string: ";
    cin >> data;

    string out = "";
    int count = 0;

    for (char bit : data) {
        out += bit;

        if (bit == '1')
            count++;
        else
            count = 0;

        if (count == 5) {     // After 5 ones add 0
            out += '0';
            count = 0;
        }
    }

    cout << "After Bit Stuffing: " << out << endl;
    return 0;
}
