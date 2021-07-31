#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
//global variables
int n = 5;//processes
int m = 4;//resources


void* Threadrun(int i, int avail[m], int max[n][m], int allo[n][m], int need[n][m]) {
	//this is run by all threads
	int j;
	printf("Thread has started\n");
	for(j=0; j<m; j++){
		avail[j] = avail[j] - need[i][j];//takes from available resources
		allo[i][j] = allo[i][j] + need[i][j];//those resources go to allo
		need[i][j] = 0;
	}
	//thread now holds max resources. avail is lower and need is zero
	printf("Thread has finished\n");
	printf("Thead is releasing resources\n");
	for(j=0; j<m; j++){
		//freeing resources means:
		avail[j] = avail[j] + max[i][j];//avail increases by max
		allo[i][j] = allo[i][j] - max[i][j];//allo decreases by max
		need[i][j] = max[i][j];//need is set equal to max
	}
	printf("New Available: ");
	for (j=0; j<m; j++){
		printf("%d ", avail[j]);
	}
	printf("\n");
	return NULL;
}

int Run(int avail[m], int max[n][m], int allo[n][m], int need[n][m], pthread_t tid[n]) {
	int valid = 1;
	int i = 0;
	int j = 0;
	int err;
	int k = 0;
	int order[n];
	int finish[n];
	int allo2[n][m];
	int avail2[m];
	int need2[n][m];

	//Duplicating Arrays ================================
    for(i = 0;i < n; i++){
        for(j = 0; j < m; j++){
            allo2[i][j]=allo[i][j];
        }
    }
	for(i = 0;i < 4; i++){
            avail2[i]=avail[i];
    }
	for(i = 0;i < n; i++){
        for(j = 0; j < m; j++){
            need2[i][j]=need[i][j];
        }
    }
    //Duplicating Arrays ================================

	for (i = 0; i < n; i++){
		order[i] = -1;
		finish[i] = 1;
		for (j = 0; j < m; j++){
			if(allo2[i][j] != 0){
				finish[i] = 0;
			}
		}
	}
	i = 0;
	while(i < n){//we have to run through this loop until no i satisfies condition
		valid = 1;
		//find index i which satisfies condition
		if(finish[i] == 0){
			
			for(j=0; j<m; j++){
				if (need[i][j] > avail2[j]){
					valid = 0;
				}//valid is 1 if need <= work every time
			}
			if(valid == 1){//an i satisfying the condition has been found
				//we release resources for this thread
                
				for(j=0; j<m; j++){
					avail2[j] = avail2[j] + allo2[i][j];
					allo2[i][j] = 0;
					need2[i][j] = max[i][j];				
				}
                
				finish[i] = 1;
				order[k] = i;
				k++;
				i = 0;//search the list from top with the new avail values
			} else {
				i++;
			}
		} else {
			i++;
		}
		//every loop, i is incremented or set to 0, and if set to zero, finish[i] is set to 1
	}
	//we know that at this point all of finish is 1, because no deadlocks are possible with our safety algorithm
	//order stores the safe sequence
	int length = k;
	printf("Safe Sequence is: ");
	for(k=0;k<length; k++){
		printf("%d ", order[k]);
	}
	
	//SECOND HALF OF RUN---------------------------------------------
	i = 0;//holds placement in safe sequence
	for(i=0;i<length; i++){
		printf("--> Customer/Thread %d\n", order[i]);
		printf("Allocated resources: ");
		for (j=0; j<m; j++){
			printf("%d ", allo[i][j]);
		}
		printf("\n");
		printf("Needed: ");
		for (j=0; j<m; j++){
			printf("%d ", need[i][j]);
		}
		printf("\n");
		printf("Available: ");
		for (j=0; j<m; j++){
			printf("%d ", avail[j]);
		}
		printf("\n");

		//run thread function
		printf("TID: %s", tid[order[i]]);
		err = pthread_create(&(tid[order[i]]), NULL, Threadrun(order[i], avail, max, allo, need), NULL);
		if (err != 0){
			printf("Thread error\n");
		} else {
			pthread_join(tid[order[i]], NULL);//wait until it completes
		}
		
	}
	//all threads in sequence ve been called and finished this pt
	return 0;
}

int RQ(int avail[m], int max[n][m], int allo[n][m], int need[n][m], char *line) {
	int i;
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
			//printf("error checking process on argument -%s-\n", bit);
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
				//printf("error checking req on argument -%s-\n", bit);
			}
		}
	}
	bit = strtok(NULL, " ");
	if (bit != NULL){
		printf("Too many arguments given\n");
		return -1;
	}
	if (valid == 0) {
		printf("Invalid Request\n");
		return -1;
	}
	
	//print status for testing purposes
	/*
	for (j = 0; j < m; j++){
		printf("%d, ", req[j]);
	}
	printf("\n");
	*/

//the process number is now held in process. the resource request numbers are held in req[]
//request algorithm starts--------------------------------------------
//first we check that all requests are below the need. requiring a for loop of m items
	valid = 1;
	for (j = 0; j < m; j++){
		if (req[j] > need[process][j]){
			valid = 0;
			//printf("req[j] = %d exceeds need[process][j] = %d\n", req[j], need[process][j]);
		}
	}
	if(valid == 0){
		printf("Request Denied: exceeds needed resources\n");
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
		printf("Request Denied: exceeds available resources\n");
	}
	if(valid == 1){		
		for (j = 0; j < m; j++){//temporarily change arrays for the safety algorithm
			avail[j] = avail[j] - req[j];
			allo[process][j] = allo[process][j] + req[j];
			need[process][j] = need[process][j] - req[j];
		}
	}
	//SAFETY ALGORITHM STARTS HERE---------------------------
	int work[m];
	int finish[n];
	for (i = 0; i < n; i++){
		finish[i] = 1;
		for (j = 0; j < m; j++){
			if(allo[i][j] != 0){
				finish[i] = 0;
			}
		}
	}
	for (j = 0; j < m; j++){
		work[j] = avail[j];
	}
	i = 0;
	while(i < n){//we have to run through this loop until no i satisfies condition
		valid = 1;
		//find index i which satisfies condition
		if(finish[i] == 0){
			for(j=0; j<m; j++){
				if (need[i][j] > work[j]){
					valid = 0;
				}//valid is 1 if need <= work every time
			}
			if(valid == 1){//an i satisfying the condition has been found
				//we pretend this program has finished and releases resources
				for(j=0; j<m; j++){
					work[j] = work[j] + allo[i][j];
				}
				finish[i] = 1;
				
				i = 0;
			} else {
				i++;
			}
		} else {
			i++;
		}
		//every loop, i is incremented or set to 0, and if set to zero, finish[i] is set to 1
	}
	//check if all have finished
	valid = 1;
	for(i=0; i<n; i++){
		if(finish[i] == 0){
			valid = 0;
		}
	}
	//SAFETY ALGORITHM ENDS HERE-----------------------------------------------
	//valid holds the result of the alg
	if (valid == 1){//safety alg returned true
		printf("State is safe and request is satisfied\n");
		//record that this process request was successfully completed for run alg
		//this probably means store it in an array
	} else {
		//then return arrays to original state if safety algorithm is not satisfied
		for(j=0; j<m; j++){
			avail[j] = avail[j] + req[j];
			allo[process][j] = allo[process][j] - req[j];
			need[process][j] = need[process][j] + req[j];
		}
		printf("Request Denied: Safety Algorithm Failed\n");
		return -1;
	}
	
	return 0;
}

int RL(int avail[m], int max[n][m], int allo[n][m], int need[n][m], char *line) {
	int j;
	int i;
	int rel[m];
	int valid = 1;	

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
			//printf("error checking process on argument -%s-\n", bit);
		}
	}
	//printf("test2: process = %d\n", process);

//second step is extract resource releases from command
	for (j = 0; j < m; j++) {
		bit = strtok(NULL, " ");
		if (bit == NULL){
			printf("Not enough arguments given\n");
			return -1;
		}
		rel[j] = atoi(bit);
		if (rel[j] == 0) {
		//atoi returns 0 if invalid input, so if 0 is returned, manually check if bit == "0"
			int result = strcmp(bit, "0");
			if (result != 0) {
				valid = 0;
				//printf("error checking req on argument -%s-\n", bit);
			}
		}
	}
	bit = strtok(NULL, " ");
	if (bit != NULL){
		printf("Too many arguments given\n");
		return -1;
	}
	if (valid == 0) {
		printf("Invalid Arguments\n");
		return -1;
	}

//the process number is now held in process. the resource release numbers are held in rel[]
	valid = 1;
	for (j = 0; j < m; j++){
		if (rel[j] > allo[process][j]){//if trying to release more than currently allocated
			valid = 0;
		}
	}
	if(valid == 0){
		printf("Release exceeds allocated resources\n");
		return -1;
	}
	//at this point the request is valid, update arrays
	for (j = 0; j < m; j++){
		allo[process][j] = allo[process][j] - rel[j];
		need[process][j] = need[process][j] + rel[j];
		avail[j] = avail[j] + rel[j];
	}

	return 0;
}

//MAIN------------------------------------------------------------------------------
int main(int argc, char **argv) {
	setbuf(stdout, NULL);

	//first initialize all variables. right now some are hard coded, until file input and argument input is coded

	int i, j; //i loops through processes. j loops through resources
	char line[64];
	char line2[64];
	char *bit;

	//second, fill max array and find values of n and m
	//FILE INPUT STARTS HERE==============================================
	//recall there will be m rows and n columns

	FILE* maxin = fopen("sample4_in.txt", "r");
	char a = 0;//cycles through characters in file
	int hold = 0; //this is for 2 digit numbers
	i = 0;//holds row
	j = 0;//holds column
	int temp[20][20];
	while ((a = fgetc(maxin)) != EOF){
		if(isdigit(a)){//add number to hold
			hold = (int)a - 48 + 10 * hold;
			temp[i][j] = hold;
		} else if (a == '\n'){//save number and increment i and set j to 0
			temp[i][j] = hold;
			hold = 0;
			i++;
			j = 0;
		} else if (a == ','){//save number and continue
			temp[i][j] = hold;
			hold = 0;
			j++;
		}
	}


	n = i + 1;
	m = j + 1;

	int max[n][m];
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			max[i][j] = temp[i][j];
		}
	}


	fclose(maxin);

	//FILE INPUT ENDS HERE==============================================


	printf("Number of Customers: %d\n", n);//---------print1
	if (argc != m+1) {
		printf("Missing command line arguments, exiting with error code -1\n");
		return -1;
	}

	pthread_t tid[n];

	//initialize the other 3 main arrays

	int avail[m]; //this is set to be equal to the arguments
	for (i = 0; i < m; i++) {
		avail[i] = atoi(argv[i+1]);
	}
	printf("Currently Available resources: ");//---------print2
	for(i = 0; i < m; i++){
		printf("%d ", avail[i]);
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

	printf("\nMaximum resources from file:"); //---------print3
	for (i = 0; i < n; i++) {
		printf("\n");
		for (j = 0; j < m; j++) {
			printf("%d ", max[i][j]);
		}
	}
	printf("\n");
	//-----------------------------------------------------------------------the main loop
	int cont = 1;
	while (cont) { 

		//-----------take input
		printf("Enter Command: ");
		scanf("%[^\n]%*c", line);
		//printf("input is -%s-\n", line);

		//----------parse input
		//the input can be one word or one word followed by ints. first check one word commands, the RL & RQ
		if (strcmp(line, "Exit") == 0) {
			//Exit code----------------------------------------------------------
			printf("Now Exiting Program\n");
			cont = 0;
		} else if (strcmp(line, "Status") == 0) {
			//status display code------------------------------------------------
			
				
			printf("Available Resources:\n");
			for(i = 0; i < m; i++){
				printf("%d ", avail[i]);
			}
	
			printf("\nMaximum Resources:\n");
			for (i = 0; i < n; i++) {
				printf("\n");
				for (j = 0; j < m; j++) {
					printf("%d ", max[i][j]);
				}
			}
			printf("\nAllocated Resources:\n");
			for (i = 0; i < n; i++) {
				printf("\n");
				for (j = 0; j < m; j++) {
					printf("%d ", allo[i][j]);
				}
			}
			printf("\nNeed Resources:\n");
			for (i = 0; i < n; i++) {
				printf("\n");
				for (j = 0; j < m; j++) {
					printf("%d ", need[i][j]);
				}
			}
			printf("\n");
		} else if (strcmp(line, "Run") == 0) {
			//run code-----------------------------------------------------------
			Run(avail, max, allo, need, tid);
			
		} else {//one word commands have been checked, now check if command is RL or RQ
			
			strcpy(line2, line);
			bit = strtok(line2, " ");
			if (strcmp(bit, "RQ") == 0) {
				//-----------------------------call RQ fxn
				RQ(avail, max, allo, need, line);

			} else if (strcmp(bit, "RL") == 0) {
				//Process Release code-------------------------------------------
				RL(avail, max, allo, need, line);
			} else {
				printf("Invalid Input\n");
			}
		}
	}
	//printf("Program Terminated\n");
	return 0;
}
