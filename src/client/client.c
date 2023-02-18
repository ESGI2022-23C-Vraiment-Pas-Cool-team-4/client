/*
 * Created by : Charbel SALHAB, Andrei MALICEK, Janin MICHEL-MATHIAS
 * Date : 24/02/2023
 * "program allowing you to create your own hotel with number of rooms and type of room and service offered.
 * The rooms can be reserved by customers according to the criteria of the hotel."
 */

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <stdlib.h>
#include <pthread.h>
#include "../../includes/sockets.h"

#pragma comment(lib, "ws2_32.lib")



int charToInt(char* str) {
    int result = 0;
    char currentChar;

    for (int i = 0; i < strlen(str); i++) {
        currentChar = str[i];
        if (currentChar < 48 || currentChar > 57) {
            result = -1;
            break;
        } else {
            result *= 10;
            result += currentChar - 48;
        }
    }

    return result;
}

int main() {

    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_addr;

    char ip[16];
    char port[6];

    // opening the conf file to get the ip address of the server and the port number
    FILE* config_file = fopen("server.conf", "r");

    if (config_file == NULL) {
        printf("Error opening config file\n");
        return 1;
    }

    fscanf(config_file, "%s %s", ip, port);

    int p = charToInt(port);

    //initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    //create a socket for the client
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Failed to create socket. Error Code : %d", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //configure the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(p);

    //connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection error\n");
        WSACleanup();
        return 1;
    }

    User user;
    char msg[60];
    recv(client_socket, msg, 60, 0);

    printf("%s\n", msg);
    scanf("%s %s", user.nom, user.mdp);

    //send data to the server
    char message[60];
    snprintf(message, 60, "%s %s", user.nom, user.mdp);

    if (send(client_socket, message, strlen(message), 0) < 0) {
        printf("Send failed. Error Code : %d", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    //close the socket and cleanup Winsock
    closesocket(client_socket);
    WSACleanup();

    //closing the conf file
    fclose(config_file);

    return 0;
}
