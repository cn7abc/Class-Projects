/* “I Jacob Rogers (ja573625) affirm that this
program is entirely my own work and that I have neither developed my code together with any
another person, nor copied any code from any other person, nor permitted my code to be copied
or otherwise used by any other person, nor have I copied, modified, or otherwise used programs
created by others. I acknowledge that any violation of the above terms will be treated as academic
dishonesty.”
*/

// ja573625
// Jacob Rogers
// CIS 3360, Fall 2018
// November-4-2018

// A program to generate checksums for 8, 16, and 32 bits.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define DEBUG 0

int main(int argc, char **argv){

	int inputLength = -1, padFlag = 0, j, i = 0, counter = 0;
	char c, fc, *text;
	long unsigned int total = 0, termOne = 0,
	termOneB = 0, termOneC = 0, termOneD = 0, termTwo = 0, termTwoB = 0, termTwoC = 0, termTwoD = 0; 

	char *fname1 = argv[1];
	int sizeParam = atoi(argv[2]);

	FILE *inputFile = fopen(fname1,"r");


	if(sizeParam == 8 || sizeParam == 16 || sizeParam == 32)
		;
	else
		fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
	

	// 8 bit checksum.
	if(sizeParam == 8){
		while(!feof(inputFile)){
			fscanf(inputFile,"%c", &c);

			// Add each 8 bit ascii value one at a time.
			total += c;
			total = total & 0xFF;
			inputLength++;
		}

		total -= 10;

		rewind(inputFile);
		printf("\n");
		// Print the input to the screen.
		while(!feof(inputFile)){
			fscanf(inputFile, "%c", &c);
			printf("%c", c);
			j++;
			if(j == 80){
				printf("\n");
				j = 0;
			}
		}	
		
		printf("%2d bit checksum is %8lx for all %4d chars\n", 8, total, inputLength);
	}

	// 16 bit checksum.
	if(sizeParam == 16){

		while(!feof(inputFile)){
			fscanf(inputFile,"%c", &fc);
			inputLength++;
		}
		rewind(inputFile);
		

		if(inputLength % 2 != 0){
			inputLength++;
			padFlag = 1;
		}
		
		
		text = malloc(sizeof(char) * inputLength);

		// Store the entire text file in an array, padding with X if required.
		for(i = 0; i < inputLength; i++){
			if((i == inputLength - 1) && padFlag == 1)
				text[i] = 'X';
			else{
				fscanf(inputFile,"%c", &c);
				text[i] = c;
			}
		}	

		// Take one 8-bit ascii value, shift it to the left by 8, bitwise OR it with the next term to make a combined 16-bit term.
		// Make two of these and then add them together, continune until the end.

		for(i = 0; i < inputLength; i+=2){
			if(i == 0){
				termOne = text[0];
				termOne = termOne << 8;
				termOneB = text[i+1];
				termOne = termOne | termOneB; 
			}
			else{
				termOne = total;
			}
			
			if(i == 0)
				termTwo = text[i+2];
			else
				termTwo = text[i];
			
			termTwo = termTwo << 8;
			if(i == 0)
				termTwoB = text[i+3];
			else
				termTwoB = text[i+1];
			
			termTwo = termTwo | termTwoB;
			
			
			total = termOne + termTwo;
			total = total & 0xFFFF;

			termOne = 0;
			termOneB = 0;
			termTwo = 0;
			termTwoB = 0;

			if(i==0)
				i +=2;
		}

		// Base Case.
		if(inputLength == 2){
			termOne = text[0];
			termOne = termOne << 8;
			termOneB = text[1];
			termOne = termOne | termOneB;
			total = termOne;
		}


		printf("\n");
		// Print the input to the screen.
		for(i=0; i < inputLength; i++){
			printf("%c",text[i]);
			j++;
			if(j == 80){
				printf("\n");
				j = 0;
			}
		}	
		printf("\n");
		printf("%2d bit checksum is %8lx for all %4d chars\n", 16, total, inputLength);

		free(text);
	}

	// 32 bit checksum.
	if(sizeParam == 32){
		while(!feof(inputFile)){
			fscanf(inputFile,"%c", &fc);
			inputLength++;
		}

		rewind(inputFile);
		// Calculate the length of the pad required.
		padFlag = 4 - (inputLength % 4);
		if(inputLength == 4)
			padFlag = 0;
		inputLength += padFlag;
		
		text = malloc(sizeof(char) * inputLength);

		// Store the entire text file in an array, padding with X if required.
		for(i = 0; i < inputLength; i++){
			fscanf(inputFile,"%c", &c);
				text[i] = c;
			if(padFlag == 3){
				text[inputLength - 3] = 'X';
				text[inputLength - 2] = 'X';
				text[inputLength - 1] = 'X';
			}
			if(padFlag == 2){
				text[inputLength - 2] = 'X';
				text[inputLength - 1] = 'X';
			}
			if(padFlag == 1){
				text[inputLength - 1] = 'X';
			}
		}

		
		for(i = 0; i < inputLength; i+=4){
			if(i == 0){
				termOne = text[0];
				termOne = termOne << 8;
				
				termOneB = text[i+1];
				termOne = termOne | termOneB; 
				termOne = termOne << 8;

				termOneC = text[i+2];
				termOne = termOne | termOneC;
				termOne = termOne << 8;

				termOneD = text[i+3];
				termOne = termOne | termOneD;
			}
			else{
				termOne = total;
			}
			
			if(i == 0){
				j = 4;
			}
			else{
				j = 0;
			}
			if(inputLength > 4){
				termTwo = text[i+(j++)];
			}
			if(inputLength > 5){
				termTwo = termTwo << 8;
				termTwoB = text[i+(j++)];
				termTwo = termTwo | termTwoB;
			}
			if(inputLength > 6){
				termTwo = termTwo << 8;
				termTwoC = text[i+(j++)];
				termTwo = termTwo | termTwoC;
			}
			if(inputLength > 7){	
				termTwo = termTwo << 8;
				termTwoD = text[i+(j++)];
				termTwo = termTwo | termTwoD;
			}

			total = termOne + termTwo;
			total = total & 0xFFFFFFFF;

			termOne = 0;
			termOneB = 0;
			termTwo = 0;
			termTwoB = 0;
			j = 0;

			if(i==0)
				i +=4;
		}

		printf("\n");
		// Print the input to the screen.
		for(i=0; i < inputLength; i++){
			printf("%c",text[i]);
			j++;
			if(j == 80){
				printf("\n");
				j = 0;
			}
		}	

		printf("\n");
		printf("%2d bit checksum is %8lx for all %4d chars\n", 32, total, inputLength);

	}


	fclose(inputFile);

	return 0;
}
