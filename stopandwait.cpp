#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of frames to send: ";
    cin >> n;

    cout << "\n--- STOP AND WAIT ARQ SIMULATION ---\n\n";

    for (int i = 1; i <= n; i++) {
        cout << "Sending Frame " << i << endl;

        char ack;
        cout << "Is ACK received for frame " << i << "? (y/n): ";
        cin >> ack;

        while (ack != 'y') {
            cout << "ACK not received! Resending Frame " << i << endl;
            cout << "Is ACK received now? (y/n): ";
            cin >> ack;
        }

        cout << "ACK received for Frame " << i << "\n\n";
    }

    cout << "All frames sent successfully.\n";
    return 0;
}
