/*
 * lookup1 : straight linear search through a local file
 * 	         of fixed length records. The file name is passed
 *	         as resource.
 */
#include <string.h>
#include "dict.h"
#include <sys/stat.h>
#include <fcntl.h>

int lookup(Dictrec * sought, const char * resource) {
	Dictrec dr;
	static FILE * in;
	static int first_time = 1;

	if (first_time) { 
		first_time = 0;
		in = fopen(resource,"r");
		/* open up the file
		 *
		 * Fill in code. */
	}

	/* read from top of file, looking for match
	 *
	 * Fill in code. */
	rewind(in);
	while(!feof(in)) {
		/* Fill in code. */
		fread(&dr,sizeof(dr),1,in);
		if(strcmp(dr.word,sought->word)==0)
		{
			strcpy(sought->word,dr.word);
			strcpy(sought->text,dr.text);
			return FOUND;
		}
	}

	return NOTFOUND;
}
