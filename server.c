
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 4321 
  char* keys[9] = {"entendido\n", "#965874580*\n", "connecting people\n", "me gusta el chocolate\n", "ESGOLODROBO\n", "amarillo\n", "Heisenberg\n", "indefinido\n", "Colombia\n"};

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[128] = {0}; 
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    
    int level = 1;
    printLevel(1);

    while (level <= 9){
        valread = read( new_socket , buffer, 128); 
    if(compareKey(buffer, level) == 1){
        level++;
        printLevel(level);
    }
    clearBuff(buffer);
    }
    return 0; 
} 



void clearBuff(char* buffer){
    int i;
    for (i=0; i<128; i++){
        buffer[i] = '\0';
    }
    return;
}

void printLevel( int level){
    switch(level)
    {
        case 1:
            printf("NIVEL 1\n");
            break;
        case 2:
            printf("NIVEL 2\n");
            break;
        case 3:
            printf("NIVEL 3\n");
            break;
        case 4:
            printf("NIVEL 4\n");
            break;
        case 5:
            printf("NIVEL 5\n");
            break;
        case 6:
            printf("NIVEL 6\n");
            break;
        case 7:
            printf("NIVEL 7\n");
            break;
        case 8:
            printf("NIVEL 8\n");
            break;
        case 9:
            printf("NIVEL 9\n");
            break;
    }
}

int compareKey (char* buffer, int level){

    if(strcmp(buffer, keys[level-1]) == 0)
       return 1;

    return 0;
}