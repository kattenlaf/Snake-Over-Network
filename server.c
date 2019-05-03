#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include <unistd.h>
#include "snake.h"

#define MSG_LEN 2000

//declare server handle
void *server_handler (void *fd_pointer);

int main()
{

  int listenfd, connfd, *new_sock;
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr; 
   
  listenfd = socket(AF_INET,SOCK_STREAM,0);
  if (listenfd == -1) {
    perror("Could not create Socket \n"); 
  }

	puts("Socket Created");
  
   bzero(&servaddr,sizeof (servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = INADDR_ANY;
   servaddr.sin_port = htons(8888);
   
   if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
   {
	   perror("bind failed");
	   return 1;
   }
   puts("bind success");
   listen(listenfd, 5);
   

  puts("Waiting for connections");
  clilen = sizeof(cliaddr);
  while ((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen))) {
		puts("Connection accepted");
		
		pthread_t server_thread;
    new_sock = malloc(1);
    *new_sock = connfd;
		pthread_create(&server_thread,NULL,server_handler,(void*) new_sock);
	}
	if (connfd < 0)
	{
		perror("Accept Failed");
		return 1;
	}
	return 0;
}

void *server_handler (void *fd_pointer)
{
	printf("Hello Server Handler \n");
	int sock = *(int *)fd_pointer;
  int read_size, write_size;
  char *message;
	static char client_message[MSG_LEN];
  message = " \nHello Server Handler \n";


	static int send_once = 0;
	if (send_once < 1)
	{
    send_once++;
	}

    while((read_size = recv(sock,client_message,MSG_LEN,0)) > 0)
   {
     // This is for checking if it's a telnet connection, telnet connections have ascii values
     // 10 and 13 appended, thus we have to do this check to determine what to do next
     int snd_char = client_message[read_size-2];
     int lst_char = client_message[read_size-1];
     printf("Char values are : %d %d\n", snd_char, lst_char);
     if ( snd_char == 13 && lst_char == 10 ) {
       // This is a telnet connection
       client_message[read_size-2] = '\0';
       client_message[read_size-1] = '\0';
       read_size -= 2;
     }
     printf("Read Size %d \n", read_size);
     printf("Client message is %s\n", client_message);

     // Write the one command to the file
     FILE *fp;
     fp = fopen("commands.txt", "w");
     fputs(client_message, fp);
     fclose(fp);

     write(sock,client_message,strlen(client_message));
     // Clear the message sent
     memset(client_message, 0, MSG_LEN * (sizeof client_message[0]) );
     // Here using the messages of the client, I need to forward the commands to the game
   }
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
	else if(read_size == -1)
    {
        perror("recv failed");
    }
    close(sock);
    free(fd_pointer);
    return 0;
}