#include<bits/stdc++.h>
using namespace std;

#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    int cfd;
    struct sockaddr_in addr;

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

    const char* ip = "127.0.0.1";

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Connect to server
    if (connect(cfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    cout << "Connected to the server" << endl;

    char buff[1024];

    while (true) {
        cout << "Enter message (type 'exit' to quit): ";
        string msg;
        getline(cin, msg);

        if (msg == "exit")
            break;

        // Send message to server
        send(cfd, msg.c_str(), msg.size(), 0);

        // Receive ACK
        memset(buff, 0, sizeof(buff));
        int n = read(cfd, buff, sizeof(buff));

        if (n > 0) {
            cout << "ACK from server: " << buff << endl;
        } else {
            cout << "Server disconnected." << endl;
            break;
        }
    }

    close(cfd);
    return 0;
}
