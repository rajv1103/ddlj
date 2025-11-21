#include <iostream>
using namespace std;

int main() {
    int n, w;
    cout << "Enter number of frames: ";
    cin >> n;

    cout << "Enter window size: ";
    cin >> w;

    cout << "\n--- SELECTIVE REPEAT ARQ SIMULATION ---\n\n";

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
            cout << "Frame " << lost << " lost!" << endl;
            cout << "Selective Repeat: Resending ONLY frame " << lost << endl;
        } else {
            cout << "All frames acknowledged for this window.\n";
        }

        next = end + 1; // Move window
        cout << endl;
    }

    cout << "All frames sent successfully.\n";
    return 0;
}
