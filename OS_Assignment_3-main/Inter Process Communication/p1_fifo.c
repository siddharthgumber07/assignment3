#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>

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

int main() {
    int fileA, fileB;

    int res;
    char txt[100];	
    char * path_A = "fifo1";
    char * path_B = "fifo2";
    
    char str[51][12] = {{0}};

	string_generator(str);
    printf("\n%s\n", "These are the randomly genereated strings!!!");
	for(int i = 1; i <= 50; i++) {
		for(int j = 0; j < 12; j++) {
			if(j == 0) {
				printf("%d ", str[i][j]);
			}
			else printf("%c", str[i][j]);
		}
		printf("\n");
	}


    mkfifo(path_A, 0666);
    mkfifo(path_B, 0666);


	int end = 1;
	while(1) {
		if(fileA == -1) {
			perror("ERROR!!! FIFO1 can't be accessed!!!");
		}

		printf("Sending Strings Indexed from %d to %d\n", end, end + 4);
		
		for(int i = end; i < end + 5; i++) {
			fileA = open(path_A, O_WRONLY);
			res = write(fileA, str[i], sizeof(str[i]) + 1);
			sleep(1);	
			close(fileA);
		}

		fileB = open(path_B, O_RDONLY);
		res = read(fileB, txt, sizeof(txt));
		close(fileB);

		if(res == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}

		int index = atoi(txt);
 		printf("Max. ID returned -> %s\n\n", txt);
		end = index + 1;
		if(end >= 50){
			exit(EXIT_SUCCESS);
		}
	}

    return 0;
}