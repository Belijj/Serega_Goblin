#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

#define SOCKET_OPENING_ERROR -1
#define BIND_ERROR -2
#define LISTEN_ERROR -2
#define ZBS 0

using namespace std;
const int PORT = 8888;

int main()
{
    int server_fd;
    int new_socket;
    long valread;

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    char *hello = "Vi kto takie? ja vas suda ne zval!\n";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_fd == 0){
        cout << "Socket failed" << endl;
        exit(SOCKET_OPENING_ERROR);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    cout << PORT << endl;
    cout << htons(PORT) << endl;

    int bind_result = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    if(bind_result < 0){
        cout  << "BIND Failed" << endl;
        exit(BIND_ERROR);
    }

    int listen_result = listen(server_fd, 10);
    if(listen_result < 0){
        cout  << "Listen Failed" << endl;
        exit(LISTEN_ERROR);
    }
    cout << "Listening on port: " << PORT << endl;
    
        while(true){
            cout << "Waiting for new connection ..." << endl;
            new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            if(new_socket < 0){
                continue;
            }
            char buffer[30000] = {0};
            valread = read(new_socket, buffer, 30000);
            cout << "Number of bytes received: " << valread << endl;
            if(valread > 0){
                cout << "Message received: " << buffer << endl;
            }
            write(new_socket, hello, strlen(hello));
            cout << "Hello message sent" << endl;
            close(new_socket);
        }
    exit(ZBS);
}
