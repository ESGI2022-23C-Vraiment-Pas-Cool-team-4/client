/*
 * Created by : Charbel SALHAB, Andrei MALICEK, Janin MICHEL-MATHIAS
 * Date : 24/02/2023
 * "program allowing you to create your own hotel with number of rooms and type of room and service offered.
 * The rooms can be reserved by customers according to the criteria of the hotel."
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

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

char* checklogin(){
    
    char *nom,*mdp;
    query *user;

    user->type = "GetUser";
    user->paramsName = malloc(sizeof(char*)* 20);
    user->paramsValue = malloc(sizeof(char*)*20);
    user->paramsName[0] = "username";
    user->paramsName[1]="password";

    printf("login : ");
    scanf("%s", nom);
    printf("mdp : ");
    scanf("%s", mdp);

    user->paramsValue[0]= nom;
    user->paramsValue[1] = mdp;
    char* requete = concatene(user);
    return requete;

}


int client(char *query) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char ip[16];
    char port[6];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    // opening the conf file to get the ip address of the server and the port number
    FILE* config_file = fopen("conf/server.conf", "r");
    
    if (config_file == NULL) {
        printf("Error opening config file\n");
        return 1;
    }

    fscanf(config_file, "%s %s", ip, port);

    // Create the TCP server socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock == INVALID_SOCKET) {
        printf("Error creating socket: %d", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    int p = charToInt(port);
    
    // Set up the address for the server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(p);
    //printf("[+]TCP server socket created. \n");

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Error connecting to server: %d", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    //printf("[+]Connected to the server.\n");

    // Create buffers to store the name and mdp fields
    char buffer[1024];
    
    //char username[100];
    //char password[100];
    
    //printf("Client : %s, %s\n", buffer1, buffer2);
    
    //sscanf(query, "querry: GetUser\nparams:\nusername: %s\npassword: %s", username, password);
    
    // Send the name buffer over a socket connection
    if (send(sock, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
        printf("Error sending name data: %d", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // // Send the mdp buffer over a socket connection
    // if (send(sock, password, strlen(password), 0) == SOCKET_ERROR) {
    //     printf("Error sending mdp data: %d", WSAGetLastError());
    //     closesocket(sock);
    //     WSACleanup();
    //     return 1;
    // }
    memset(buffer, 0, sizeof(buffer));

    // Receive data from the server
    if (recv(sock, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
        printf("Error receiving data: %d", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    
    // printf("Server: %s\n", buffer);

    // Close the socket, disconnect from the server
    closesocket(sock);
    //printf("[+]Disconnected from the server.\n");

    // Closing the conf file
    fclose(config_file);

    // Clean up Winsock
    WSACleanup();

    return 0;
}

