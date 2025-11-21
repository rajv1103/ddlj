// server.cpp
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Fill server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Any local IP
    address.sin_port = htons(8080);       // Port number

    // 3. Bind socket to IP + Port
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // 4. Listen for incoming connection
    listen(server_fd, 3);

    cout << "Waiting for connection...\n";

    // 5. Accept client connection
    socklen_t addrlen = sizeof(address);
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);

    // 6. Read message from client
    read(new_socket, buffer, 1024);
    cout << "Message from client: " << buffer << endl;

    close(new_socket);
    close(server_fd);
}
