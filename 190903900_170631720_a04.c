#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	setbuf(stdout, NULL);
	printf("test\n");
	//first initialize all variables

	int n = 3; //how many processes
	int m = 5; //how many resource types
	int i, j; //i loops through processes. j loops through resources
	char line[64];

	//initialize the 4 main arrays

	int avail[n]; //this is set to be equal to the arguments
	for (i = 0; i < n; i++) {
		avail[i] = 6;
	}

	int max[n][m]; //initialized to sample_in
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			max[i][j] = 3; //----------------temporarily hard coded during testing. fix later
		}
	}

	//start the command entry loop
	int cont = 1;

	while (cont) { //the main loop

		//take input
		scanf("%s", &line);

		//parse input
		//the input can be one word or one word followed by ints. first check one word commands, the RL & RQ
		if (strcmp(line, "status") == 1) {

		} else if (strcmp(line, "Exit") == 0) {
			//Exit code----------------------------------------------------------
			printf("Now Exiting Program\n");
			cont = 0;
		} else if (strcmp(line, "Status") == 0) {
			//status display code------------------------------------------------
			printf("Status display code\n");
		} else if (strcmp(line, "Run") == 0) {
			//run code-----------------------------------------------------------
			printf("run code\n");
		} else {//one word commands have been checked, now check if command is RL or RQ

			char *bit = strtok(line, " ");
			if (strcmp(bit, "RQ") == 0) {
				//Process Request Code-------------------------------------------
				for (i = 0; i < n; i++) {
					char *bit = strtok(line, " ");
				}

			} else if (strcmp(bit, "RL") == 0) {
				//Process Release code-------------------------------------------
			} else {
				printf("Invalid Input\n");
			}
			printf("Looping now\n");
			cont = 0;
		}
	}

	return 0;
}
