#include <bits/stdc++.h>
using namespace std;

#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

void sendFile(int cfd, ifstream &f) {
    char buff[1024];  

    while (true) {
        f.read(buff,5);
        int bytesRead = f.gcount();     // actual bytes read
        if (bytesRead <= 0) break;      // EOF

        if (send(cfd, buff, bytesRead, 0) < 0) {
            perror("Send Failed");
            return;
        }

        // Wait for ACK
        memset(buff, 0, sizeof(buff));
        int n = read(cfd, buff, sizeof(buff) - 1);
        if (n <= 0) {
            cout << "ACK error" << endl;
            return;
        }

        buff[n] = '\0';
        cout << "Server says: " << buff << endl;
    }

    // Notify server that file transfer ended
    string endMsg = "EOF";
    send(cfd, endMsg.c_str(), endMsg.size(), 0);
}

int main() {
    int cfd;
    struct sockaddr_in addr;

    // Create socket
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    const char* ip = "127.0.0.1";

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Connect to server
    if (connect(cfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    cout << "Connected to server\n";

    ifstream f("file.txt", ios::binary);
    if (!f.is_open()) {
        perror("File not found");
        exit(EXIT_FAILURE);
    }

    sendFile(cfd, f);

    close(cfd);
    return 0;
}
