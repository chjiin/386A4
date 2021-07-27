#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global variables
int n;
int m;

int RQ( avail, max, allo, need, line) { //execute request algorithm and safety algorithm if needed
	int process;
	int req[m];
	int i;
	int j;
	char *bit = strtok(line, " ");

	process = atoi(bit);
	for (j = 0; j < m; j++) {
		bit = strtok(line, " ");
		req[j] = atoi(bit);
	}
	if (RQ(avail, max, allo, need, req, process) == 0) {
		printf("State is safe, and request is satisfied");
	} else {
		printf("Request denied");
	}
	return 0;
	return 0;
}

int main( int argc, char **argv ) {
	if (argc < 4) {
		printf("Missing command line arguments, exiting with error code -1\n");
		return -1;
	}

	argv++;
	setbuf(stdout, NULL);
	printf("test\n");
	//first initialize all variables. right now some are hard coded, until file input and argument input is coded

	n = 3; //how many processes
	m = 5; //how many resource types
	int i, j; //i loops through processes. j loops through resources
	char line[64];
	char *bit;
	char c;
	int process;
	int req[m];
	int flag;

	//initialize the 4 main arrays

	int avail[n]; //this is set to be equal to the arguments
	for (i = 0; i <=n; i++) {
		avail[i] = atoi(argv[i]);
	}

	int max[n][m]; //initialized to sample_in
	for (i = 0; i < m; i++) {
		for (j = 0; j <= n; j++) {
			max[i][j] = 3; //----------------temporarily hard coded during testing. fix later
		}
	}
	for (i = 0; i <m; i++) {
		printf("\n");
		for (j = 0; j <=n; j++) {
			printf("%d ", max[i][j]); //----------------temporarily hard coded during testing. fix later
		}
	}

	int allo[n][m]; //initialized to zero
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			allo[i][j] = 0;
		}
	}

	int need[n][m]; //always equal to max - allo
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			need[i][j] = max[i][j];
		}
	}

	int cont = 1;

	while (cont) { //------------the main loop

		//-----------take input
		//scanf("%s", &line); scanf doesnt read whole line
		scanf("%[^\n]%*c", line);
		printf("input is -%s- and length is %d\n", line, strlen(line));

		line[strlen(line) - 1] = '\0';

		printf("input is -%s-\n", line);

		//----------parse input
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
			bit = strtok(line, " ");
			if (strcmp(bit, "RQ") == 0) {
				printf("RQ recognized\n");
				
				//-----------------------------check if there are the right number of only integers, then call fxn
				i = 0;//counting number
				j = 0;
				flag = 1; //is the command valid
				bit = strtok(NULL, " ");
				while (bit != NULL && flag == 1) { //for every number
					printf("checking bit %s\n", bit);
					//printf( " %s\n", bit );
					c = bit[i];
					for (i = 0; i < strlen(bit); i++) {	//for every character
						if (isdigit(c) != 1) {//if any single character is not a digit, we know the command is invalid
							flag = 0;
						}
						c = bit[i];
					}
					bit = strtok(NULL, " ");
					j++;
				}
				if (flag == 1 && j == (1 + m)) {//if every input was a number and there are the correct amount of numbers, proceed with command
					printf("valid command");
					/*
					 if (RQ(avail, max, allo, need, line) == 0) {
					 printf("RQ returned valid");
					 } else {
					 printf("RQ did not return valid");
					 }
					 */
				}

			} else if (strcmp(bit, "RL") == 0) {
				//Process Release code-------------------------------------------
			} else {
				printf("Invalid Input\n");
			}
			printf("Looping now\n");
			//cont = 0;
		}
	}

	return 0;
}
