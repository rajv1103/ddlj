#include <iostream>
#include <string>
using namespace std;

int main() {
    string data, delim;
    cout << "Enter the data to send: ";
    getline(cin, data);

    cout << "Enter the delimiter: ";
    getline(cin, delim);

    string stuffed = "S" + delim; // start flag + delimiter

    // Stuffing
    for (int i = 0; i < data.size(); i++) {
        bool match = true;

        // check if delimiter found in data
        for (int k = 0; k < delim.size(); k++) {
            if (i + k >= data.size() || data[i + k] != delim[k]) {
                match = false;
                break;
            }
        }

        if (match) { 
            stuffed += delim;  // add delimiter again
            i += delim.size() - 1;
        }

        stuffed += data[i];
    }

    stuffed += delim + "E";   // end delimiter + end flag

    cout << "Data after stuffing: " << stuffed << endl;

    // ---------------- DESUTFFING -----------------

    string cleaned = "";
    for (int i = 0; i < data.size(); i++) {
        bool match = true;

        for (int k = 0; k < delim.size(); k++) {
            if (i + k >= data.size() || data[i + k] != delim[k]) {
                match = false;
                break;
            }
        }

        if (match) {
            i += delim.size() - 1; // skip delimiter
            continue;
        }

        cleaned += data[i];
    }

    cout << "\nData after destuffing: " << cleaned << endl;

    return 0;
}
