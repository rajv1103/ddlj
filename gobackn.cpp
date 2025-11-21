#include <iostream>
using namespace std;

int main() {
    int n, w;
    cout << "Enter number of frames: ";
    cin >> n;

    cout << "Enter window size: ";
    cin >> w;

    cout << "\n--- GO-BACK-N ARQ SIMULATION ---\n\n";

    int next = 1;

    while (next <= n) {
        int end = min(next + w - 1, n);

        cout << "Sending Frames: ";
        for (int i = next; i <= end; i++)
            cout << i << " ";
        cout << endl;

        int lost;
        cout << "Enter lost frame number (0 for none): ";
        cin >> lost;

        if (lost >= next && lost <= end) {
            cout << "Frame " << lost << " lost!\n";
            cout << "Go-Back-N: Resending entire window...\n\n";
            // Window remains same, resend again
        } else {
            cout << "All frames acknowledged.\n\n";
            next = end + 1;  // Move window forward
        }
    }

    cout << "All frames sent successfully.\n";
    return 0;
}
