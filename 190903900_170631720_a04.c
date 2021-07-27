
int main() {

	printf("test\n");
	//first initialize all variables
	int n = 3; //how many processes
	int m = 5; //how many resource types
	int i, j; //i loops through processes. j loops through resources
	
	
	//initialize the 4 main arrays
	
	int max[][];
	for(i=0; i<n; i++) {
		for(j=0;j<m;j++) {
			max[i][j] = 0;
		}
	}
	

	//start the command entry loop
	int cont = 1;

	while (cont){

		//take input
		char line[64];

		scanf("%[^\n]", line);

		//parse input
		//the input can be one word or one word followed by ints. first check if its a one word command
		if(strcmp(line, "status") == 1){

		} else if(strcmp(line, "Exit") == 1){
			//Exit code----------------------------------------------------------
			printf("Now Exiting Program\n");
			cont = 0;
		} else if(strcmp(line, "Status") == 1){
			//status display code------------------------------------------------

		} else if(strcmp(line, "Run") == 1){
			//run code-----------------------------------------------------------

		} else {//one word commands have been checked, now check if command is RL or RQ

			char* bit = strtok(line, " ");
			if (strcmp(bit, "RQ") == 1){
				//Process Request Code-------------------------------------------
				
				
				
				
			} else if (strcmp(bit, "RL") == 1){
				//Process Release code-------------------------------------------
			}

		}
		return 0;
	}

}
