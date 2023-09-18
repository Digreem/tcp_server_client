#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SERVER_PORT 8080

#define MESSAGE_MAX_LENGTH  100
#define RESPONSE_MAX_LENGTH  150

char message[MESSAGE_MAX_LENGTH];
char response[RESPONSE_MAX_LENGTH];

void communicate(int sockfd)
{

    int n;
    for (;;) {
        bzero(message, MESSAGE_MAX_LENGTH);
        bzero(response, RESPONSE_MAX_LENGTH);

        printf("Enter the string (write 'exit' to close TCP connection): ");
        n = 0;
        //get user input
        //fflush(stdin);
        while ((message[n++] = getchar()) != '\n')
            ;
        write(sockfd, message, strlen((const char*)message));


        read(sockfd, response, RESPONSE_MAX_LENGTH);
        printf("From Server : %s", response);

        if ((strncmp(message, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
	printf("Hello from client!!!\n");

	int client_socket;
	struct sockaddr_in serv_addr;

	 //client socket create and verification
	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_socket == -1)
	{
		printf("# Error: socket creation failed # \n");
		exit(0);
	}
	else
		printf("# Client socket successfully created #\n");

	// assign IP, PORT
	memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(SERVER_PORT);

    // connect the client socket to server socket
    if(connect(client_socket, (sockaddr*)&serv_addr, sizeof(serv_addr)) != 0 )
    {
    	printf("# Connection with server failed #\n");
    	exit(0);
    }
    else
    	printf("# Connected to server successfully #\n");

    communicate(client_socket);

    close(client_socket);
    printf("# Client socket closed #\n");

	return 0;
}
