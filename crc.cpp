#include <iostream>
#include <vector>
using namespace std;

// Function to perform XOR division (CRC)
vector<int> xorDivide(vector<int> data, vector<int> gen) {
    int n = gen.size();
    vector<int> temp = data;

    for (int i = 0; i <= temp.size() - n; i++) {
        if (temp[i] == 1) {
            for (int j = 0; j < n; j++) {
                temp[i + j] ^= gen[j];
            }
        }
    }

    // Remainder is last n-1 bits
    vector<int> rem(n - 1);
    for (int i = 0; i < n - 1; i++)
        rem[i] = temp[temp.size() - n + 1 + i];

    return rem;
}

int main() {
    int m, n;

    cout << "Enter degree of generator: ";
    cin >> n;

    vector<int> gen(n + 1);
    cout << "Enter generator polynomial bits: ";
    for (int i = 0; i <= n; i++)
        cin >> gen[i];

    cout << "Enter degree of frame: ";
    cin >> m;

    vector<int> frame(m + 1);
    cout << "Enter frame bits: ";
    for (int i = 0; i <= m; i++)
        cin >> frame[i];

    // Append n zeros to frame
    vector<int> data = frame;
    for (int i = 0; i < n; i++)
        data.push_back(0);

    // Calculate remainder
    vector<int> rem = xorDivide(data, gen);

    // Create transmitted frame
    vector<int> transmitted = frame;
    for (int x : rem)
        transmitted.push_back(x);

    cout << "\nRemainder: ";
    for (int x : rem) cout << x;

    cout << "\nTransmitted Frame: ";
    for (int x : transmitted) cout << x;
    cout << "\n";

    // -------- RECEIVER SIDE ------------

    cout << "\nReceiver enter degree of received frame: ";
    cin >> m;

    vector<int> recv(m + 1);
    cout << "Enter received frame: ";
    for (int i = 0; i <= m; i++)
        cin >> recv[i];

    // Recompute remainder
    vector<int> recvRem = xorDivide(recv, gen);

    cout << "\nRemainder at Receiver: ";
    bool error = false;
    for (int x : recvRem) {
        cout << x;
        if (x != 0) error = true;
    }

    if (!error)
        cout << "\nNo Error Detected\n";
    else
        cout << "\nError Detected!\n";

    return 0;
}
