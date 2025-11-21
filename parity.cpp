#include <iostream>
using namespace std;

int main() {
    string data;
    cout << "Enter binary data: ";
    cin >> data;

    int count1 = 0;
    for(char c : data) {
        if(c == '1') count1++;
    }

    // Even Parity
    char evenParity = (count1 % 2 == 0) ? '0' : '1';

    // Odd Parity
    char oddParity = (count1 % 2 == 0) ? '1' : '0';

    cout << "\nOriginal Data : " << data;
    cout << "\nEven Parity Bit Added : " << data + evenParity;
    cout << "\nOdd Parity Bit Added  : " << data + oddParity << endl;

    return 0;
}
