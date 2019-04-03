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
// September-30-2018

// A program to encrypt plaintext, using a key, to cipher text using the Vigenere cipher method.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv){

	int keyLength = 0, flag = 0, i=0, j, PClength = 0, shift, k, m;
	char c;
	char *keyString;
	char plaintextString[513];
	char cipherString[513];

	char *fname1 = argv[1];
	char *fname2 = argv[2];
	FILE *keyFile = fopen(fname1,"r");
	FILE *PlainTextFile = fopen(fname2, "r");

	if(fname1 == NULL || fname2 == NULL)
		printf("Couldn't open file.\n");
	
	printf("\n\n");
	
	// READ IN THE KEY:
	// Iterate through the key file twice. 
	// In the first iteration find the length of the final key (which excludes non-alphabetic chars and spaces).
	// In the second iteration the key is saved to an array. 
	for(j = 0; j < 2; j++){

		// For the second iteration rewind the file pointer and dynamically allocate a char array of the key length.
		if(j == 1){
			rewind(keyFile);
			keyString = malloc(sizeof(char) * keyLength);
			keyString[keyLength]= '\0';
		}

		while(!feof(keyFile)){

			// Scan a char from the file.
			fscanf(keyFile,"%c", &c);

			// If it's a whitespace or if it's not alphabetic, raise a flag.
			if(isspace(c) != 0)
				flag = 1;
			if(isalpha(c) == 0)
				flag = 1;
			
			// Add to the key length if no flags were raised on the first iteration.
			if(j == 0 && flag == 0 && !feof(keyFile)){
				keyLength++;
			}

			// Add to the char aray if no flags were raised on the second iteration.
			if(j == 1 && flag == 0 && !feof(keyFile)){
				keyString[i++] = tolower(c);
			}

			flag = 0;
		}
	}

	k = 0;
	m = 0;	
	// Print the key with a line length of 80.
	printf("Vigenere Key:\n\n");
	do{
		printf("%c", keyString[m]);

		k++;
		if(k == 80){
			printf("\n");
			k = 0;
		}

		m++;
	}while(m < keyLength);

	

	// Initalize the plaintextString array with x at every index.
	for(i=0; i<=513; i++){
		if(i == 512 || i == 513)
			plaintextString[i] = '\0';
		else
			plaintextString[i] = 'x';
	}

	flag = 0;

	// READ IN THE PLAINTEXT:
	// Save it to a string and exclude incorrect chars.
	while(!feof(PlainTextFile) && PClength < 513){

		// Scan a char from the file.
		fscanf(PlainTextFile,"%c", &c);

		// If it's a whitespace or if it's not alphabetic, raise a flag.
		if(isspace(c) != 0)
			flag = 1;
		if(isalpha(c) == 0)
			flag = 1;

		if(flag == 0 && !feof(PlainTextFile))
			plaintextString[PClength++] = tolower(c);

		flag = 0;
	}

	k = 0;
	m = 0;
	// Print the plaintext with a line length of 80.
	printf("\n\n\nPlaintext:\n\n");
	do{
		printf("%c", plaintextString[m]);

		k++;
		if(k == 80){
			printf("\n");
			k = 0;
		}

		m++;
	}while(m < 512);

	printf("\n");

	// CREATE THE CIPHER-TEXT.
	for(i = 0; i < 513; i++){

		shift = keyString[i % keyLength] - 97;
	
		c = ((plaintextString[i] - 97) + shift) % 26;
		
		cipherString[i] = c + 97;

		if(i == 512)
			cipherString[i] = '\0';
	}

	j = 0;
	i = 0;
	// Print the cipher-text with a line length of 80.
	printf("\n\nCiphertext:\n\n");
	do{
		printf("%c", cipherString[i]);

		j++;
		if(j == 80){
			printf("\n");
			j = 0;
		}

		i++;
	}while(i < 512);

	free(keyString);
	fclose(keyFile);
	fclose(PlainTextFile);

	printf("\n");
	
	return 0;
}
