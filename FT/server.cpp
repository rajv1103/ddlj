#include <bits/stdc++.h>
using namespace std;

#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

void writeToFile(int ns) {
    ofstream f("recv.txt");
    if (!f.is_open()) {
        perror("File Creation Failed");
        exit(EXIT_FAILURE);
    }

    char buff[1024];

    while (true) {
        memset(buff, 0, sizeof(buff));

        int n = read(ns, buff, sizeof(buff) - 1);

        if (n <= 0) {
            cout << "Client disconnected" << endl;
            break;
        }

        buff[n] = '\0';
        cout << "Client Sends: " << buff << endl;

        f.write(buff, n);
        f << "\n";
        f.flush();

        string ack = "ACK: Received -> " + string(buff);
        send(ns, ack.c_str(), ack.size(), 0);
    }

    f.close();
}

int main() {
    int sfd, ns;
    struct sockaddr_in addr, cli;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }

    const char *ip = "127.0.0.1";

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sfd, 3) < 0) {
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(cli);

    ns = accept(sfd, (struct sockaddr *)&cli, &len);
    if (ns < 0) {
        perror("Accept Failed");
        exit(EXIT_FAILURE);
    }

    cout << "Client Connected Successfully" << endl;

    writeToFile(ns);

    close(ns);
    close(sfd);

    return 0;
}
