#include <bits/stdc++.h>
using namespace std;

#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

void sendFile(int cfd, ifstream &f) {
    char buff[1024];

    while (f.getline(buff, sizeof(buff))) {

        int len = strlen(buff);

        if (send(cfd, buff, len, 0) < 0) {
            perror("Send Failed");
            break;
        }

        // Wait for ACK
        memset(buff, 0, sizeof(buff));
        int n = read(cfd, buff, sizeof(buff) - 1);

        if (n <= 0) {
            cout << "ACK error" << endl;
            break;
        }

        buff[n] = '\0';
        cout << "Server says: " << buff << endl;
    }
}

int main() {
    int cfd;
    struct sockaddr_in addr;

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0) {
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }

    const char *ip = "127.0.0.1";

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(cfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    cout << "Connected to Server" << endl;

    ifstream f("file.txt");
    if (!f.is_open()) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    sendFile(cfd, f);

    f.close();
    close(cfd);

    return 0;
}
