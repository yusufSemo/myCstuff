// FileLib Template

#include <stdio.h>
#include <string.h>
#include "ListLib.h"

FILE* OpenFile(int argc, char *argv[])
{	
	/* declare various variables needed */
	char InputFileName[100] = {};
	char NewFileName[100] = {};
	FILE *InputFH;

	/* if argc is 2, then use argv[1] as the input file name, else print the message seen in sample output */
	if(argc == 2)
	{
		strcpy(InputFileName, argv[1]);
	}
	else
	{
		printf("Must be run with an input file name.\n");
	}

	do
	{
		/* open file with "r" mode */
		InputFH = fopen(InputFileName, "r");

		/* if file did not open */
		if(InputFH == NULL)
		{
			/* print message seen in sample output */
			printf("Enter a file name at the prompt ");
			scanf("%s", NewFileName);
			/* read in new filename */
			strcpy(InputFileName, NewFileName);
			/* open the file "r" mode */
			InputFH = fopen(NewFileName, "r");
		}
	}
	while (InputFH == NULL);

	/* return the file handle */
	return InputFH;
}

void ReadFileIntoLinkedList(FILE *DCFile, NODE **LinkedListHead)
{
	/* declare various variables needed */
	char line[200];
	char Letter;
	char DrawCommand[20] = {};
	char *token = NULL;
	char *Delimiters = ")";
	NODE *nodes = malloc(sizeof(NODE));
	int Count = 0;
	
	/* while fgets() reads the file */
	while (fgets(line, sizeof(line)-1, DCFile))
	{
		/* if line from file ends with \n, then replace \n with \0 */
		if(line[strlen(line)-1] == '\n')
		{
			line[strlen(line)-1] = '\0';
		}
		/* tokenize to get the Letter and the DrawCommand */
		token = strtok(line,"|");
		Letter = token[0];
		nodes->Letter = Letter;
		token = strtok(NULL,Delimiters);
		//nodes->DrawCommand = malloc(strlen(token)*sizeof(char)+1);
		
		strcpy(DrawCommand, token);

		
		/* Call AddDrawCommandToList with correct parameters */
		AddDrawCommandToList(Letter, DrawCommand, &nodes);
	}

}
