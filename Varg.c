// ja573625
// Jacob Rogers
// COP 3502, Spring 2017
// Jan-22-2017

// This program consists of two variadic functions to find the most commonly occuring char, and two other functions for time and difficulty.

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "Varg.h"

char fancyMostFrequentChar(char c, ...){
// Array has 3 rows and 26 columns, the 26 columns are for each letter in the alphabet, and row 1 = the number of occurances of each letter,
// row 2 = the entry time of the input letters by the user, and row 3 = a tick mark (1 or 0) used to mark each letter that is tied for the highest number of occurances.
	int alphabet[27][3] = {{0}};
	va_list argp;
	va_start(argp, c);
	int i, k, j, L, m, p, entryTime = 0, highest = 0;
	char input, output;

	// Altering the alphabet array accordingly for the first char (if the first char is not \0).
	// Doing this first entry outside of the while loop because the while loop will start after the first argument.
	if(c != '\0'){
		alphabet[c-97][1]++;
		entryTime++;
		alphabet[c-97][2]=entryTime;
	}
	// Return '\0' right away if '\0' is the first char passed to the function.
	else
		return '\0';

	// Get the input from the user and increase the alphabet array's first row (# of occurances) for each time that char is encountered.
	// increase the second row (entrytime) by one as well to record the order in which the chars were entered (to deal with ties later).
	while((input = va_arg(argp, int)) != '\0'){
		entryTime++;
		alphabet[input-97][1]++;
		alphabet[input-97][2] = entryTime;
	}

	// Find highest number of times any letter occures in the entire list from the array's first row (there could be ties).
	for(j=0;j<26;j++){
		if(highest < alphabet[j][1])
			highest = alphabet[j][1];
	}

	// Tick mark each letter that is euqal to the higest # of occurances with a 1 in the third row of the array (to deal with ties).
	for(L=0;L<26;L++){
		if(alphabet[L][1] == highest)
			alphabet[L][3] = 1;
	}

	// Find lowest entry time not equal to zero, amongst the tick marked letters.
	for(p=0;p<26;p++){
		if(alphabet[p][3] == 1 && alphabet[p][2] < entryTime)
			entryTime = alphabet[p][2];
	}

	// Find specific cell in which the lowest entryTime and highest occurances exist, hence finding the final answer.
	for(m=0;m<26;m++){
		if(alphabet[m][3] == 1 && alphabet[m][2] == entryTime)
			output = m+97;
	}

	va_end(argp);

	return output;
}


char mostFrequentChar(int n, ...){
// Array has 3 rows and 26 columns, the 26 columns are for each letter in the alphabet, and row 1 = the number of occurances of each letter,
// row 2 = the entry time of the input letters by the user, and row 3 = a tick mark (1 or 0) used to mark each letter that is tied for the highest number of occurances.
	int alphabet[27][3] = {{0}};
	int i, k, j, L, m, p, entryTime = 0, highest = 0;
	char input, output;
	va_list argp;
	va_start(argp, n);

	// Return the output of '\0' if the first input is 0 meaning 0 letters will be passed by the user.
	if(n == 0){
		output = '\0';
		return '\0';
	}
	
	// Get the input from the user and increase the alphabet array's first row (# of occurances) for each time that char is encountered.
	// increase the second row (entrytime) by one as well to record the order in which the chars were entered (to deal with ties later).
	for(i=0;i<n;i++){
			input = va_arg(argp, int);
			entryTime++;
			alphabet[input-97][1]++;
			alphabet[input-97][2] = entryTime;

	}
	// find highest number of times any letter occures in the entire list from the array's first row (there could be ties).
	for(j=0;j<26;j++){
		if(highest < alphabet[j][1])
			highest = alphabet[j][1];
	}
	// tick mark each letter that is euqal to the higest # of occurances with a 1 in the third row of the array (to deal with ties).
	for(L=0;L<26;L++){
		if(alphabet[L][1] == highest)
			alphabet[L][3] = 1;
	}
	// Find lowest entry time not equal to zero, amongst the tick marked letters.
	for(p=0;p<26;p++){
		if(alphabet[p][3] == 1 && alphabet[p][2] < entryTime)
			entryTime = alphabet[p][2];
	}
	// Find specific cell in which the lowest entryTime and highest occurances exist, hence finding the final answer.
	for(m=0;m<26;m++){
		if(alphabet[m][3] == 1 && alphabet[m][2] == entryTime)
			output = m+97;
	}
	
	va_end(argp);
	
	return output;
}

double hoursSpent(void){
	return 8.5;
}

double difficultyRating(void){
	return 2.75;
}
