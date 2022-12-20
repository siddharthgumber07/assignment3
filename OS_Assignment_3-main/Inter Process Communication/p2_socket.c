#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define name "Assignment3.socket"


int main(int arg_num, char *arg[]) {
	struct sockaddr_un server;
	int temp = 0;
	int con_socket;
	int res;
	int max = 0;
	int data;
	char txt[12];

	con_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if(con_socket == -1) {
		perror("ERROR!!! Couldn't connect to server!!!");
		exit(EXIT_FAILURE);
	}

	memset(&server, 0, sizeof(server));
	server.sun_family = AF_UNIX;
	strncpy(server.sun_path, name, sizeof(server.sun_path) - 1);

	res = bind(con_socket, (const struct sockaddr *) &server, sizeof(server));

	if(res == -1) {
		perror("!!!Bind!!!");
		exit(EXIT_FAILURE);
	}

	res = listen(con_socket, 100);
	if(res == -1) {
		perror("!!!Listen!!!");
		exit(EXIT_FAILURE);
	}

	while(1) {
		data = accept(con_socket, NULL, NULL);
		if(data == -1) {
			perror("ERROR!!! Couldn't accept!!!\n");
			exit(EXIT_FAILURE);
		}

		max = 0;
		int current = max;
		while(1) {
			res = read(data, txt, sizeof(txt));
			if(res == -1) {
				perror("ERROR!!!Couldn't read!!!\n");
				exit(EXIT_FAILURE);
			}

			txt[sizeof(txt) - 1] = 0;
			current = txt[0];

			if(!strncmp(txt, "DOWN", sizeof(txt))) {
				temp = 1;
				break;
			}

			printf("\n");
			printf("String sent by P1     :  ");		
			
			for(int i = 1; i < 11; i++) {
				printf("%c", txt[i]);
			}

			printf("\n");
			sprintf(txt, "%d", current);
			printf("ID Sent by P1         :  %s\n", txt);		

			if(current == max + 5) {
				max = current;
				res = write(data, txt, sizeof(txt));
			}	

			if(current >= 50) 
				break;
		}
		
		

		close(data);

		if(temp) {
			printf("!!!Exiting Server!!!");
			close(con_socket);
			unlink(name);
			exit(EXIT_SUCCESS);
			break;
		}
		
		if(res == -1) {
			perror("!!!Write!!!");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}