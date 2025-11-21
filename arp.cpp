#include <iostream>
#include <vector>
using namespace std;

struct ARPEntry {
    string ip;
    string mac;
};

int main() {
    // Initial ARP Table
    vector<ARPEntry> table = {
        {"192.168.1.1", "AA:BB:CC:DD:EE:01"},
        {"192.168.1.2", "AA:BB:CC:DD:EE:02"},
        {"192.168.1.3", "AA:BB:CC:DD:EE:03"}
    };

    string queryIP;
    cout << "Enter IP to search in ARP Table: ";
    cin >> queryIP;

    bool found = false;

    // Search in table
    for (auto &entry : table) {
        if (entry.ip == queryIP) {
            cout << "\nARP Reply: MAC Address is " << entry.mac << endl;
            found = true;
            break;
        }
    }

    // If not found, simulate ARP Request + Add to table
    if (!found) {
        cout << "\nIP not found in ARP table!" << endl;
        cout << "Sending ARP Request..." << endl;

        string newMac = "AA:BB:CC:DD:EE:99"; // dummy MAC
        table.push_back({queryIP, newMac});

        cout << "ARP Reply Received. Added Entry:\n";
        cout << "IP  : " << queryIP << endl;
        cout << "MAC : " << newMac << endl;
    }

    // Print Updated Table
    cout << "\n--- Updated ARP Table ---\n";
    for (auto &e : table) {
        cout << e.ip << " --> " << e.mac << endl;
    }

    return 0;
}
