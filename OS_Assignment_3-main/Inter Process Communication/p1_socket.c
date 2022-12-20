#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>

#define name "Assignment3.socket"


void string_generator(char str[][12]) {        
    srand (time(NULL));                            
    for (int j = 0; j <= 50; j++) {
        str[j][0] = j;
    }
    
    for(int i = 0; i <= 50; i++) {
		for(int j = 1; j <= 10; j++) {
			str[i][j] = rand() % 26 + 65;
		}
	}
}

int main(int arg_num, char* arg[]) {
	struct sockaddr_un address;
	int res;
	int data;
	char txt[10];

	data = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if(data == -1) {
		perror("ERROR!!! Couldn't create socket!!!\n");
		exit(EXIT_FAILURE);
	}	

	memset(&address, 0, sizeof(address));

	address.sun_family = AF_UNIX;
	strncpy(address.sun_path, name, sizeof(address.sun_path) - 1);
	res = connect(data, (const struct sockaddr *) &address, sizeof(address));

	if(res == -1) {
		perror("ERROR!!! Couldn't connect!!!\n");
		exit(EXIT_FAILURE);
	}	

	char str[51][12] = {{0}};
	string_generator(str);
	
	for(int i = 1; i <= 50; i++) {
		for(int j = 0; j < 12; j++) {
			if(j == 0) {
				printf("%d ", str[i][j]);
			}
			else printf("%c", str[i][j]);
		}
		printf("\n");
	}

	if(arg_num > 1) {
		strncpy(txt, "DOWN", sizeof("DOWN"));
		write(data, txt, sizeof(txt));
		close(data);
		exit(EXIT_SUCCESS);
	}
	else {
		int end = 1;
		while(1) {
			printf("\n");
			printf("Sending Strings Indexed from %d to %d to P2\n", end, end + 4);
			for(int i = end; i < end + 5; i++) {
				res = write(data, str[i], strlen(str[i]) + 1);
				if(res == -1) {
					perror("ERROR!!! Couldn't perform write!!!");
				}
			}

			res = read(data, txt, sizeof(txt));
			if(res == -1) {
				perror("read");
				exit(EXIT_FAILURE);
			}

			txt[sizeof(txt) - 1] = 0;
			int index = atoi(txt);
			printf("Max. ID recieved = %s\n\n", txt);
			if(index == 50) {
				printf("Strings sent successfully!!!\n");
				strncpy(txt, "DOWN", sizeof("DOWN"));
				write(data, txt, sizeof(txt));
				close(data);
				exit(EXIT_SUCCESS);
				break;
			}
			else {
				end = index + 1;
			}
		}
	}
}