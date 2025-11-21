// client.cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    const char* msg = "Hello from Client!";

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Fill server address (server IP in LAN)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // 👉 Enter server machine's LAN IP here (e.g., 192.168.1.10)
    inet_pton(AF_INET, "192.168.1.10", &serv_addr.sin_addr);

    // 3. Connect to server
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 4. Send message
    send(sock, msg, strlen(msg), 0);

    cout << "Message sent to server\n";

    close(sock);
}
