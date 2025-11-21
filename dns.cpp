#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
using namespace std;

int main() {
    string hostname;
    cout << "Enter hostname (example.com): ";
    cin >> hostname;

    // DNS Lookup
    struct hostent *hostinfo = gethostbyname(hostname.c_str());
    if (hostinfo == NULL) {
        cout << "DNS Lookup Failed!" << endl;
        return 0;
    }

    char *ip = inet_ntoa(*(struct in_addr*)hostinfo->h_addr);
    cout << "\nResolved IP: " << ip << endl;

    // Create TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    server.sin_addr.s_addr = inet_addr(ip);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        cout << "Connection Failed!" << endl;
        return 0;
    }

    // HTTP GET Request
    string request = "GET / HTTP/1.1\r\nHost: " + hostname + "\r\nConnection: close\r\n\r\n";
    send(sock, request.c_str(), request.length(), 0);

    // Read response
    char buffer[2000];
    int bytes;
    cout << "\n--- HTTP RESPONSE START ---\n";
    while ((bytes = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        cout << buffer;
    }

    cout << "\n--- HTTP RESPONSE END ---\n";

    close(sock);
    return 0;
}
