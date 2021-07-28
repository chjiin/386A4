#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//global variables
int n = 5;//processes
int m = 4;//resources

int RQ(int avail[m], int max[n][m], int allo[n][m], int need[n][m], char *line) {
	//int i;
	int j;
	int req[m];
	int valid = 1;

	//printf("line is %s\n", line);
	//first step is extract process number from command
	char *bit = strtok(line, " ");
	bit = strtok(NULL, " ");
	if (bit == NULL){
		printf("Not enough arguments given\n");
		return -1;
	}

	int process = atoi(bit);

	if (process == 0) {
		//atoi returns 0 if invalid input, so if 0 is returned, manually check if bit == "0"
		int result = strcmp(bit, "0");
		if (result != 0){
			valid = 0;
			printf("error checking process on argument -%s-\n", bit);
		}
	}
	//printf("test2: process = %d\n", process);

//second step is extract resource request amounts from command
	for (j = 0; j < m; j++) {
		bit = strtok(NULL, " ");
		if (bit == NULL){
			printf("Not enough arguments given\n");
			return -1;
		}
		req[j] = atoi(bit);
		if (req[j] == 0) {
		//atoi returns 0 if invalid input, so if 0 is returned, manually check if bit == "0"
			int result = strcmp(bit, "0");
			if (result != 0) {
				valid = 0;
				printf("error checking req on argument -%s-\n", bit);
			}
		}
	}
	bit = strtok(NULL, " ");
	if (bit != NULL){
		printf("Too many arguments given\n");
		return -1;
	}
	if (valid == 0) {
		printf("Valid = 0\n");
		return -1;
	}
	
	//print status for testing purposes
	for (j = 0; j < m; j++){
		printf("%d, ", req[j]);
	}
	printf("\n");


//the process number is now held in process. the resource request numbers are held in req[]
//request algorithm starts--------------------------------------------
//first we check that all requests are below the need. requiring a for loop of m items
	valid = 1;
	for (j = 0; j < m; j++){
		if (req[j] > need[process][j]){
			valid = 0;
			printf("req[j] = %d exceeds need[process][j] = %d\n", req[j], need[process][j]);
		}
	}
	if(valid == 0){
		printf("Given request exceeds maximum needed resources\n");
		return -1;
	}
	valid = 1;
	
	for (j = 0; j < m; j++){
		if (req[j] > avail[j]){
			valid = 0;
		}
	}
	
	if(valid == 0){
	//the request is granted but the thread has to wait until resources are freed up
		printf("Request granted. Thread is waiting\n");
	}
	if(valid == 1){	
		printf("running safety algorithm\n");
		for (j = 0; j < m; j++){//temporarily change arrays for the safety algorithm
			avail[j] = avail[j] - req[j];
			allo[process][j] = allo[process][j] - req[j];
			need[process][j] = need[process][j] - req[j];
		}
	}
	//then run safety algorithm
	

	//then return arrays to original state if safety algorithm is not satisfied

	
	return 0;
}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	printf("test\n");
	if (argc != 5) {
		printf("Missing command line arguments, exiting with error code -1\n");
		return -1;
	}
	
//first initialize all variables. right now some are hard coded, until file input and argument input is coded

	int i, j; //i loops through processes. j loops through resources
	char line[64];
	char line2[64];
	char *bit;
	//line = "test";
//initialize the 4 main arrays

	int avail[m]; //this is set to be equal to the arguments
	for (i = 0; i < m; i++) {
		avail[i] = atoi(argv[i+1]);
		printf("avail: %d\n", avail[i]);
	}
	printf("Currently Available resources: ");
	for(i = 0; i < m; i++){
		printf("%d ", avail[i]);
	}

	//FILE INPUT STARTS HERE==============================================

	FILE* maxin = fopen("sample4_in.txt", "r");
	int a = 0;
	int k = 0;
	char filestr[64];
	while ((a = fgetc(maxin)) != EOF){
		if(isdigit((int)a)){
			filestr[k] = a;
			k++;
		}
	}

	fclose(maxin);

	k = 0;
	int max[n][m]; //initialized to sample_in
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			max[i][j] = filestr[k];
			k++;
		}
	}
	
	printf("\nMaximum resources from file:");

	for (i = 0; i < n; i++) {
		printf("\n");
		for (j = 0; j < m; j++) {
			printf("%c ", max[i][j]);
		}
	}

	//FILE INPUT ENDS HERE==============================================

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
		//printf("input is -%s-\n", line);

		//line[strlen(line) - 1] = '\0';

		//printf("input is -%s-\n", line);

		//----------parse input
		//the input can be one word or one word followed by ints. first check one word commands, the RL & RQ
		if (strcmp(line, "Exit") == 0) {
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
			
			strcpy(line2, line);
			bit = strtok(line2, " ");
			if (strcmp(bit, "RQ") == 0) {
				printf("RQ recognized\n");

				//-----------------------------call RQ fxn

				if (RQ(avail, max, allo, need, line) == 0) {
					//printf("RQ returned valid\n");
				} else {
					//printf("RQ did not return valid\n");
				}

			} else if (strcmp(bit, "RL") == 0) {
				//Process Release code-------------------------------------------
			} else {
				printf("Invalid Input\n");
			}
			//printf("End of Loop\n");
			cont = 0;
		}
	}
	printf("Program Terminated\n");
	return 0;
}
