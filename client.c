#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

char *gets(char *s);

int sockfd;

void waitForEnter(){
  char c;
  while((c=getchar())!='\n'){}
}

void sendAnswer(char* answer){
  static int counter = 1;
  printf("Respuesta %d: %s\n", counter++,answer);
  write(sockfd, answer, strlen(answer));
}

void askForAnswer(){
  char buff[100];
  fgets(buff, sizeof(buff), stdin);
  int aux= strlen(buff);
  buff[aux] = '\n';
  buff[aux+1]=0;

  sendAnswer(buff);
}

int main(int argc, char *argv[])
{
    sockfd = 0;
    int n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4321);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

    waitForEnter();
    sendAnswer("entendido\n");

    waitForEnter();
    sendAnswer("#965874580*\n");

    waitForEnter();
    sendAnswer("connecting people\n");

    waitForEnter();
    sendAnswer("me gusta el chocolate\n");

    waitForEnter();
    sendAnswer("ESGOLODROBO\n");

    waitForEnter();
    sendAnswer("amarillo\n");

    waitForEnter();
    sendAnswer("Heisenberg\n");

    waitForEnter();
    sendAnswer("indefinido\n");

    waitForEnter();
    sendAnswer("Colombia\n");

    while(1){
      askForAnswer();
    }

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    }

    if(n < 0)
    {
        printf("\n Read error \n");
    }

    return 0;
}
