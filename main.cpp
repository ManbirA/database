#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <valarray>
#include "database.h"

int main() {

    int listening_soc = socket(AF_INET, SOCK_STREAM, 0);
    if (listening_soc == -1) {
        std::cout << "Cant create socket" << std::endl;
        return -1;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    // convert host to network short (translate)
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening_soc, (sockaddr*)&hint, sizeof(hint)) == -1){
        std::cout << "Cant bind" << std::endl;
        return -1;
    }

    if (listen(listening_soc, SOMAXCONN) == -1) {
        std::cout << "Cant listen" << std::endl;
        return -1;
    }

    sockaddr_in client_addr;
    socklen_t client_size = sizeof(client_addr);
    int client_soc = accept(listening_soc, (sockaddr*)&client_addr, &client_size);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client_addr,client_size, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
        std::cout << host << " Port" << service << std::endl;
    } else {
        inet_ntop(AF_INET, &client_addr.sin_addr, host, NI_MAXHOST);
        std::cout << host << " Port: " << ntohs(client_addr.sin_port) << std::endl;
    }

    close(listening_soc);
    database *db = nullptr;

    char buf[4096];
    while(true) {
        memset(buf, 0, 4096);
        int bytes_recieved = recv(client_soc, buf, 4096, 0);
        if (bytes_recieved == -1) {
            std::cout << "Error recieving" << std::endl;
            break;

        }
        if (bytes_recieved == 0) {
            std::cout << "Disconnected" << std::endl;
            break;
        }
        std::cout << std::string(buf, 0, bytes_recieved) << std::endl;
        std::string buf_s(buf);
        // Parse input

        char operation = buf_s.at(0);
        if (operation == 'N') {
            // Create new db
            int size = buf_s.at(1) - '0';
            std::string name = buf_s.substr(2, size);
            db = new database(name);
            char buf_rtr[] = "Created";
            send(client_soc, buf_rtr, sizeof(buf_rtr), 0);
        } else if (operation == 'S') {
            int key_size = buf_s.at(1) - '0';
            std::string key_name = buf_s.substr(2, key_size);
            int value_size = buf_s.at(2 + key_size) - '0';
            std::string value = buf_s.substr(3 + key_size, value_size);
            if (db == nullptr) {
                char buf_rtr[] = "DB not created, not stored";
                send(client_soc, buf_rtr, sizeof(buf_rtr), 0);
            } else {
                db->set_key_value(key_name, value);
                char buf_rtr[] = "Stored in DB";
                send(client_soc, buf_rtr, sizeof(buf_rtr), 0);
            }
            // Set key value
        } else if (operation == 'E') {
            break;
        }


        std::cout << operation << std::endl;
        send(client_soc, buf, bytes_recieved+1, 0);
    }

    close(client_soc);
    return 0;

}
