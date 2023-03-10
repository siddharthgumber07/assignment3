#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>



int main() {
    int fileA, fileB;

    int res;
    char txt[100];
	int index = 0;
    char * path_A = "fifo1";
    char * path_B = "fifo2";

    mkfifo(path_A, 0666);
    mkfifo(path_B, 0666);


	index = 0;
	int curr = index;
	while(1) {
		while(curr < index + 5) {
			sleep(2);
			fileA = open(path_A, O_RDONLY);
			res = read(fileA, txt, sizeof(txt));
			close(fileA);
			if(res == -1) {	
				perror("ERROR!!! Can't read the string!!!");
				exit(EXIT_FAILURE);
			}
			curr = txt[0];
			printf("String generated by P1 through FIFO         ->    ");		
			
			for(int i = 1; i < 12; i++) {
				printf("%c", txt[i]);
			}
			printf("\n");
			
			sprintf(txt, "%d", curr);
			printf("Index sent to P1 by P2                      ->    %s\n", txt);
			printf("\n");	
		}
		
		index = curr;
		fileB = open(path_B, O_WRONLY);
		res = write(fileB, txt, sizeof(txt));
		close(fileB);
		if(index >= 50){
			 exit(EXIT_SUCCESS);
		}
	}
    return 0;
}