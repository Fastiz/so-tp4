
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
    
    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto.\n");
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
            printf("------------- NIVEL 0 -------------\nBienvenidos al TP4 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron respondiendo correctamente los desafios de cada nivel. Además tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafio final consiste en crear un servidor que se comporte igual que yo.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafio con \"entendido\\n\"\n\nPREGUNTA PARA INVESTIGAR:\nCómo descubrieron el protocolo, la direccion y el puerto para conectarse?\n\n\n");
            break;
        case 2:
            printf("------------- NIVEL 1 -------------\n# up up left down left up right down down left *\n\nPREGUNTA PARA INVESTIGAR:\nQue diferencias hay entre TCP y UDP y en que casos conviene usar cada uno?\n\n\n");
            break;
        case 3:
            printf("------------- NIVEL 2 -------------\n-.-. --- -. -. . -.-. - .. -. --. / .--. . --- .--. .-.. .\n\nPREGUNTA PARA INVESTIGAR:\nEl puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? por qué?\n\n\n");
            break;
        case 4:
            printf("------------- NIVEL 3 -------------\nMike Echo Golf Uniform Sierra Tango Alpha Echo Lima Charlie Hotel Oscar Charlie Oscar Lima Alpha Tango Echo\n\nPREGUNTA PARA INVESTIGAR:\nQué útil abstracción es utilizada para comunicarse con sockets? se puede utilizar read(2) y write(2) para operar?\n\n\n");
            break;
        case 5:
            printf("------------- NIVEL 4 -------------\nTJ ANBYDNBCJ J NBCN JLNACQRX NB \"NBOXTXMAXKX\"\n\nPREGUNTA PARA INVESTIGAR:\nCómo garantiza TCP que los paquetes llegan en orden y no se pierden\n\n\n");
            break;
        case 6:
            printf("------------- NIVEL 5 -------------\n#FFFF00\n\nPREGUNTA PARA INVESTIGAR:\nUn servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. Qué conviene más?\n\n\n");
            break;
        case 7:
            printf("------------- NIVEL 6 -------------\nI AM THE ONE WHO KNOCKS\n\nPREGUNTA PARA INVESTIGAR:\nCómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n\n\n");
            break;
        case 8:
            printf("------------- NIVEL 7 -------------\nsizeof(int)\n\nPREGUNTA PARA INVESTIGAR:\nQué aplicaciones se pueden utilizar para ver el tráfico por la red. Muestre un ejemplo.\n\n\n");
            break;
        case 9:
            printf("------------- NIVEL 8 -------------\ndEAtP3SAlnA\n\nPREGUNTA PARA INVESTIGAR:\nsockets es un mecanismo de IPC. Qué es más eficiente entre sockets y pipes?\n\n\n");
            break;
    }
}

int compareKey (char* buffer, int level){

    if(strcmp(buffer, keys[level-1]) == 0)
       return 1;

    return 0;
}
