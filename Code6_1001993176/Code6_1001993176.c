//Yusuf Semo 1001993176 coding assignment 6
#include "ListLib.h"
#include "FileLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DrawTool.h"

int main(int argc, char *argv[])
{
    NODE *LinkedListHead;
    NODE *TempPtrs = malloc(sizeof(NODE)*sizeof(char)+1);;
    LinkedListHead = NULL;
    
    FILE *InpFH;
    InpFH = OpenFile(argc,argv);
    ReadFileIntoLinkedList(InpFH, &LinkedListHead);

    char Map[MAXMAPSIZE][MAXMAPSIZE];
    int MyMapSize;
    InitializeMap(Map);
    PrintMap(Map);
    char tool[2] = {0};
    int from = 0;
    int to = 0;
    int count = 0;
    char mark[2] = {};
    printf("Please enter 1-3 letters ");
    char letters[4] = {};
        scanf("%s",letters);
        while(strlen(letters) > 3 || strlen(letters) == 0)
        {
            printf("inproper input ");
            scanf("%s",letters);
        }
    
    while(tool[0] != 'Q')
    {

        char *Delimiters = "(),";
        char *Token = NULL;
        char DrawCommand[20];
        for(int i = 0; i < strlen(letters); i++)
        {
            char currentLetter = toupper(letters[i]);
            // Find the first node containing your first letter and
            // get back a bookmark to the next node
            TempPtrs = FindLetter(LinkedListHead, currentLetter, DrawCommand);
            // Either check the strlen() of draw command (0 means it was set to NULL)
            // or check if element [0] of draw command is '\0'
            // You want to continue to loop while your draw command has something in it

            while (strlen(DrawCommand) > 0)
            {
                //tokenize and draw the command
                Token = strtok(DrawCommand,Delimiters);
                // Look for the next node containing the letter
                // draw command will be NULL if not found
                
       

        
            strcpy(tool,Token);
            tool[0] = toupper(tool[0]);
            if(tool[0] != 'Q')
            {
            
        
                Token = strtok(NULL,Delimiters);
                from = atoi(Token);
 
                Token = strtok(NULL,Delimiters);
                to = atoi(Token);
    
                Token = strtok(NULL,Delimiters);
                count = atoi(Token);
                if(count <0 || count > MyMapSize || to <0 || to >= MyMapSize || from <0 || from >= MyMapSize)
                {
                    printf("\nThat draw command is out of range");
                }

                Token = strtok(NULL,Delimiters);
                if(Token != NULL)
                {
                   strcpy(mark,Token);
                }
        
                if(Token[0] == '\n')
                {
                    strcpy(mark,"X");
                }
                if(tool[0] == 'P')
                {
                   Map[from][to] = mark[0];
                }
                    if(tool[0] == 'V' || tool[0] == 'H')
                {
                    DrawLine(Map,from,to,tool[0],count,mark[0]);
                }
        
                PrintMap(Map);
            }
            TempPtrs = FindLetter(TempPtrs, currentLetter, DrawCommand);
            }
         }
    }
    return 0;
}