#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//global variables
int n;
int m;

int RQ(int avail[], int max[][], int allo[][], int need[][], char line) {
	//int i;
	int j;
	int req[m];
	int valid;

	char *bit = strtok(NULL, " ");
	int process = atoi(bit);

	if (process == 0) {
		//atoi returns 0 if invalid input, so if 0 is returned, manually check if bit == "0"
		valid = 0;
	}

	for (j = 0; j < m; j++) {
		bit = strtok(line, " ");
		req[j] = atoi(bit);
		if (process == 0 && strcmp("0", bit) == 0) {
			valid = 0;
		}
	}
	if (valid == 0) {
		printf("Invalid RQ arguments\n");
		return -1;
	}
//request algorithm
//temp measure to remove warnings

	return 0;
}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	printf("test\n");
	if (argc < 4) {
		printf("Missing command line arguments, exiting with error code -1\n");
		return -1;
	}
//first initialize all variables. right now some are hard coded, until file input and argument input is coded

	n = 4; //how many processes
	m = 5; //how many resource types
	int i, j; //i loops through processes. j loops through resources
	char line[64];
	char *bit;

//initialize the 4 main arrays

	int avail[n]; //this is set to be equal to the arguments
	for (i = 0; i < n; i++) {
		avail[i] = atoi(argv[i]);
	}

	int max[n][m]; //initialized to sample_in
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			max[i][j] = 3; //----------------temporarily hard coded during testing. fix later
		}
	}

	int allo[n][m]; //initialized to zero
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			allo[i][j] = 0;
		}
	}

	int need[n][m]; //always equal to max - allo
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			need[i][j] = max[i][j];
		}
	}
	int cont = 1;

	while (cont) { //------------the main loop

		//-----------take input
		//scanf("%s", &line); scanf doesnt read whole line
		scanf("%[^\n]%*c", line);
		//printf("input is -%s-\n", line);

		//line[strlen(line) - 1] = '\0';

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

				//-----------------------------call RQ fxn

				if (RQ(avail, max, allo, need, line) == 0) {
					printf("RQ returned valid");
				} else {
					printf("RQ did not return valid");
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
