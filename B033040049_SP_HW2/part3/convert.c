/*
 * convert.c : take a file in the form 
 *  word1
 *  multiline definition of word1
 *  stretching over several lines, 
 * followed by a blank line
 * word2....etc
 * convert into a file of fixed-length records
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "dict.h"
#define BIGLINE 512

int main(int argc, char **argv) {
	FILE *in;
	FILE *out;        /* defaults */
	char line[BIGLINE];
	static Dictrec blank;
	
	/* If args are supplied, argv[1] is for input, argv[2] for output */
	if (argc==3) {
		if ((in =fopen(argv[1],"r")) == NULL){DIE(argv[1]);}
		if ((out =fopen(argv[2],"w")) == NULL){DIE(argv[2]);}	
	}
	else{
		printf("Usage: convert [input file] [output file].\n");
		return -1;
	}

	/* Main reading loop : read word first, then definition into dr */

	/* Loop through the whole file. */
	while (!feof(in)) {
		
		
		/* Create and fill in a new blank record.
		 * First get a word and put it in the word field, then get the definition
		 * and put it in the text field at the right offset.  Pad the unused chars
		 * in both fields with nulls.
		 */
		memset(blank.word,0,WORD);
		memset(blank.text,0,TEXT);
		memset(line,0,BIGLINE);

		/* Read word and put in record.  Truncate at the end of the "word" field.
		 *
		 * Fill in code. */
		fgets(blank.word,WORD,in);
		blank.word[strlen(blank.word)-1]='\0';
		if(strcmp(blank.word,"")==0)
			break;
		
		/* Read definition, line by line, and put in record.
		 *
		 * Fill in code. */
		while(fgets(line,BIGLINE,in))
		{
			if(strcmp(line,"\n")==0)
				break;
			strcat(blank.text,line);
		}
		

		fwrite(&blank, sizeof(blank), 1, out); 
		/* Write record out to file.
		 *
		 * Fill in code. */
	}

	fclose(in);
	fclose(out);
	return 0;
}
