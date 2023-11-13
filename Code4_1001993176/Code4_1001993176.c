//Yusuf Semo 1001993176 coding assignment 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DrawTool.h"
int main(void)
{
    char Map[MAXMAPSIZE][MAXMAPSIZE];
    int MyMapSize;
    InitializeMap(Map, &MyMapSize);
    PrintInstructions();
    PrintMap(Map,MyMapSize);
    //char tool[2] = {};
    char tool[2] = {0};
    int from = 0;
    int to = 0;
    int count = 0;
    char mark[2] = {};
    
    while(tool[0] != 'Q')
    {
        printf("Enter draw command (enter Q to quit) ");
    
        char *Delimiters = "(),";
        /*char tool[2] = {0};
        int from = 0;
        int to = 0;
        int count = 0;
        char mark[2] = {};
        */
        char TokenPhrase[MAXMAPSIZE];
        fgets(TokenPhrase, MAXMAPSIZE-1, stdin);
        char *Token = NULL;

        Token = strtok(TokenPhrase,Delimiters);
        strcpy(tool,Token);
        tool[0] = toupper(tool[0]);
        if(tool[0] == 'Q')
        {
            return 0;
        }
        Token = strtok(NULL,Delimiters);
        from = atoi(Token);
        if(from <0 || from >= MyMapSize)
        {
            printf("\nThat draw command is out of range");
        }
        Token = strtok(NULL,Delimiters);
        to = atoi(Token);
        if(to <0 || to >= MyMapSize)
        {
            printf("\nThat draw command is out of range");
        }
    
        Token = strtok(NULL,Delimiters);
        count = atoi(Token);
        if(count <0 || count > MyMapSize)
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
        PrintMap(Map,MyMapSize);

    }
    return 0;
}