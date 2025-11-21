#include <iostream>
using namespace std;

int main() {
    int threshold = 16;        // ssthresh
    int cwnd = 1;              // Congestion Window
    int rounds;

    cout << "Enter number of rounds: ";
    cin >> rounds;

    cout << "\n--- TCP Congestion Control Simulation ---\n";
    cout << "Round\tcwnd\tPhase\n";

    for (int i = 1; i <= rounds; i++) {

        if (cwnd < threshold) {
            // Slow Start Phase → exponential growth
            cout << i << "\t" << cwnd << "\tSlow Start\n";
            cwnd *= 2;
        }
        else {
            // Congestion Avoidance Phase → linear growth
            cout << i << "\t" << cwnd << "\tCongestion Avoidance\n";
            cwnd += 1;
        }

        // Simulated Packet Loss (optional example)
        if (cwnd >= 32) {
            cout << "*** Packet Loss Detected ***\n";
            threshold = cwnd / 2;    // AIMD: Multiplicative Decrease
            cwnd = 1;                // Reset to 1 (Slow Start)
            cout << "New ssthresh: " << threshold << "\n\n";
        }
    }

    return 0;
}
