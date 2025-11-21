#include <bits/stdc++.h>
using namespace std;

#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 3000

string fn() {
    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt) - 1] = '\0';
    return string(dt);
}

void fun(int ns){
    ofstream f("recv.txt", ios::binary);  // binary mode
    if(!f.is_open()){
        perror("Recv file not created");
        exit(EXIT_FAILURE);
    }

    char buff[10240];
    while (true) {
        memset(buff, 0, sizeof(buff));

        int n = read(ns, buff, sizeof(buff));
        if (n <= 0) {
            cout << "Client disconnected" << endl;
            break;
        }

        // Check for EOF
        if (n == 3 && strncmp(buff,"EOF",3) == 0) break;

        cout << "Client Sends: " << buff << endl;

        f.write(buff, n);
        f.flush();

        string ack = "ACK: Received -> " + string(buff, n);  // safe for binary
        send(ns, ack.c_str(), ack.size(), 0);
    }

    f.close();
}

int main() {
    int sfd, ns;
    struct sockaddr_in addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    const char* ip = "127.0.0.1";

    // Create socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("Server socket not created");
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Bind socket
    if (bind(sfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Can't bind");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(sfd, 3) < 0) {
        perror("Can't listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server running, waiting for client...\n";

    // Accept client
    ns = accept(sfd, (struct sockaddr*)&client_addr,&client_len);
    if (ns < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    cout << "Client connected\n";
    fun(ns);

    close(ns);
    close(sfd);

    return 0;
}
