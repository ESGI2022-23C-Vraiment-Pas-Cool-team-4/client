/*
 * Created by : Charbel SALHAB, Andrei MALICEK, Janin MICHEL-MATHIAS
 * Date : 24/02/2023
 * "program allowing you to create your own hotel with number of rooms and type of room and service offered.
 * The rooms can be reserved by customers according to the criteria of the hotel."
 */

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../sockets.h"

int charToInt(char* str){
    int result = 0;
    char currentChar;

    for(int i = 0; i < strlen(str); i++){
        currentChar = str[i];
        if(currentChar < 48 || currentChar > 57){
            result = -1;
            break;
        }else {
            result *= 10;
            result += currentChar - 48;
        }
    }

    return result;
}

int main(){

    char ip[16];
    char *port;

    // opening the conf file to get the ip address of the server and the port number
    FILE *config_file = fopen("server.conf", "r");
    
    if (config_file == NULL) {
        printf("Error opening config file\n");
        return 1;
    }

    fscanf(config_file, "%s %s", ip, port);

    int p = charToInt(port);

    //create the TCP server socket
    int socketClient = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addrClient;

    /*
    1-set the address family to be used as the Internet Protocol v4.

    2-set the port number to be used for the connection.

    3-set the IP address to be used for the connection using the inet_addr function which converts the passed IP address string to an 32-bit integer.
    */

    addrClient.sin_addr.s_addr = inet_addr(ip);
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(p);

    //connect to the server
    connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
    // printf("connecté\n");

    User user;
    char msg[60];
    recv(socketClient, msg, 60, 0);

    printf("%s\n",msg);
    scanf("%s %s", user.nom,user.mdp);

    //send data over a socket connection
    send(socketClient, &user, sizeof(user), 0);

    //close the socket, disconnect from the server
    close(socketClient);
    //closing the conf file
    fclose(config_file);
    return 0;
}