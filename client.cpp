#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int PORT = 8888;
using namespace std;

int main(int argc, char *argv[]) {
    
    if (argc > 1) {
        PORT = atoi(argv[1]);
    }

    int sock, new_socket;
    long valread;
    struct sockaddr_in serv_address;
    int addrlen = sizeof(serv_address);
    char *hello = "Hello from server";

    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr) <= 0) {
        cout << "Invalid address" << endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_address, sizeof(serv_address)) < 0) {
        cout << "Connection Failed" << endl;
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    cout << "Hello message sent" << endl;
    valread = read(sock, buffer, 1024);
    cout << "Message Received: " << buffer << endl;

    return 0;
}
