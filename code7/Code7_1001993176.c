/*Yusuf Semo 1001993176 coding assignment 7*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "MovieTheaterLib.h"
#include "QueueLib.h"
#include "BSTLib.h"
#include "ListLib.h"
#include "StackLib.h"

void PrintReceipts(SNODE **StackTop)
{
	if(*StackTop == NULL)
	{
		printf("No receipts\n");
	}
	else
	{
		printf("Today's receipts\n\n");
		SNODE *TempPtr = *StackTop;
		while (TempPtr != NULL)
		{
			printf("\n\nReceipt #%d\n\n", TempPtr->ReceiptNumber);
			printf("\t%s\n\n", TempPtr->MovieTheaterName);
			char MTicket[5];
			while(TempPtr->TicketList != NULL)
			{
				ReturnAndFreeLinkedListNode(&(TempPtr->TicketList), MTicket);
				printf("\t%s",MTicket);
			}
			pop(StackTop);
			TempPtr = TempPtr->next_ptr;
			
		}
	}
}

BNODE *PickAndDisplayTheater(BNODE *BSTRoot, char MovieTheaterMap[][MAXCOLS], int *MapRow, int *MapCol)
{
	BNODE *MyTheater = NULL;
	char zip[6] = {};
	char MyDims[6] = {};
	
	printf("\n\nPick a theater by entering the zipcode\n\n");
	InOrder(BSTRoot);
	printf("Enter zip ");
	scanf("%5s", zip);
	BNODE* result = SearchForBNODE(BSTRoot, zip);

	if(result == NULL)
	{
		printf("\ntheater not found\n");
	}
	else
	{
		char *Token = NULL;
		char *Delimeter = "x";
		char reset[20] = {};
		strcpy(reset, result->Dimensions);
		Token = strtok(result->Dimensions,Delimeter);
		char Phrase1[5] = {};
		strcpy(Phrase1,Token);
		*MapRow = atoi(Phrase1);
		Token = strtok(NULL,Delimeter);
		char Phrase2[6] = {};
		strcpy(Phrase2,Token);
		*MapCol = atoi(Phrase2);
		strcpy(result->Dimensions, reset);
		int value = ReadMovieTheaterFile(MovieTheaterMap, result->FileName, *MapRow, *MapCol);
		if(value == 0)
		{
			printf("\nUnable to print that seat map at this time.  Check back later.\n");
		}
		else
		{
			PrintSeatMap(MovieTheaterMap, *MapRow, *MapCol);
		}
		return result;
	}
	
				
	// Traverse the BST in order and print out the theaters in zip code order - use InOrder()			
	
	// Prompt for a zip

	// Call SearchForBNODE()

	// If theater is not found, then print message
	
	// If theater is found, then tokenize the theater's dimensions and
	// pass those dimensions and the MovieTheaterMap and the theater's filename
	// to ReadMovieTheaterFile()

	// If ReadMovieTheaterFile() returns FALSE, then print
	// "Unable to print that seat map at this time.  Check back later."
	// else call PrintSeatMap()

	// return the found theater
}	

void ReadFileIntoQueue(FILE *QueueFile, QNODE **QH, QNODE **QT)
{
	char FileLine[100];
	while(fgets(FileLine,sizeof(FileLine)-1,QueueFile))
	{
		enQueue(FileLine,QH,QT);
	}
	
}

void ReadFileIntoBST(FILE *BSTFile, BNODE **BSTnode)
{
	char BSTFileLine[200];
	char *token = NULL;
	char *Delimeter = "|";
	char name[20] = {};
	char zipC[7] = {};
	char FN[15] = {};
	char Dimens[8] = {};
	while(fgets(BSTFileLine,sizeof(BSTFileLine)-1,BSTFile))
	{
		token = strtok(BSTFileLine,Delimeter);
		strcpy(name, token);
		token = strtok(NULL,Delimeter);
		strcpy(zipC, token);
		token = strtok(NULL,Delimeter);
		strcpy(FN, token);
		token = strtok(NULL,Delimeter);
		strcpy(Dimens, token);
		AddBSTNode(BSTnode, name,zipC,FN,Dimens);

	}
	//	read the passed in file and tokenize each line and pass the information to AddBSTNode
}

void get_command_line_parameter(char *argv[], char ParamName[], char ParamValue[])
{
	int i = 0; 
	
	while (argv[++i] != NULL)
	{
		if (!strncmp(argv[i], ParamName, strlen(ParamName)))
		{
			strcpy(ParamValue, strchr(argv[i], '=') + 1);
		}
	}
}

int PrintMenu()
{
	int choice = 0;
	
	printf("\n\n1.	Sell tickets to next customer\n\n");
	printf("2.	See who's in line\n\n");
	printf("3.	See the seat map for a given theater\n\n");
	printf("4.	Print today's receipts\n\n");
	printf("Choice : ");
	scanf("%d", &choice);
	
	while (choice < 1 || choice > 4)
	{
		printf("Invalid choice.  Please reenter. ");
		scanf("%d", &choice);
	}
	
	return choice;
}

int main(int argc, char *argv[])
{
	int i, j, k;
	FILE *queueFile = NULL;
	FILE *zipFile = NULL;
	char arg_value[20];
	char queuefilename[20];
	char zipfilename[20];
	int ReceiptNumber = 0;
	int choice = 0;
	int SeatNumber;
	char Row;
	char Ticket[5];
	int ArrayRow, ArrayCol;
	int MapRow, MapCol;
	char MovieTheaterMap[MAXROWS][MAXCOLS] = {};
	LNODE *TicketLinkedListHead = NULL;
	QNODE *QueueHead = NULL;
	QNODE *QueueTail = NULL;
	BNODE *BSTRoot = NULL;
	BNODE *MyTheater = NULL;
	SNODE *StackTop = NULL;
	int NumberOfTickets = 0;
	
	if (argc != 4)
	{
		printf("%s QUEUE=xxxxxx ZIPFILE=xxxxx RECEIPTNUMBER=xxxxx\n", argv[0]);
		exit(0);
	}
	
	get_command_line_parameter(argv, "QUEUE=", queuefilename);
	get_command_line_parameter(argv, "ZIPFILE=", zipfilename);
	get_command_line_parameter(argv, "RECEIPTNUMBER=", arg_value);
	ReceiptNumber = atoi(arg_value);
	
	queueFile = fopen(queuefilename, "r");
    if (queueFile == NULL)
    {
        printf("Error opening %s\n", queuefilename);
        exit(1);
    }

    zipFile = fopen(zipfilename, "r");
    if (zipFile == NULL)
    {
        printf("Error opening %s\n", zipfilename);
        exit(1);
    }
	ReadFileIntoQueue(queueFile, &QueueHead, &QueueTail);
	ReadFileIntoBST(zipFile, &BSTRoot);
	
	while (QueueHead != NULL)
	{
		choice = PrintMenu();
	
		switch (choice)
		{
			case 1 :
				printf("\n\nHello %s\n", QueueHead->name);				
				MyTheater = PickAndDisplayTheater(BSTRoot, MovieTheaterMap, &MapRow, &MapCol);
				if (MyTheater != NULL)
				{
					printf("\n\nHow many movie tickets do you want to buy? ");
					scanf("%d", &NumberOfTickets);
					for (i = 0; i < NumberOfTickets; i++)
					{
						do
						{
							printf("\nPick a seat (Row Seat) ");
							scanf(" %c%d", &Row, &SeatNumber);
							Row = toupper(Row);
							ArrayRow = (int)Row - 65;
							ArrayCol = SeatNumber - 1;
						
							if ((ArrayRow < 0 || ArrayRow >= MapRow) ||
								(ArrayCol < 0 || ArrayCol >= MapCol))
							{
								printf("\nThat is not a valid seat.  Please choose again\n\n");
							}		
						}
						while ((ArrayRow < 0 || ArrayRow >= MapRow) ||
							   (ArrayCol < 0 || ArrayCol >= MapCol));
						
						if (MovieTheaterMap[ArrayRow][ArrayCol] == 'O')
						{	
							MovieTheaterMap[ArrayRow][ArrayCol] = 'X';
							sprintf(Ticket, "%c%d", Row, SeatNumber); 
							InsertNode(&TicketLinkedListHead, Ticket);
						}
						else
						{
							printf("\nSeat %c%d is not available.\n\n", Row, SeatNumber);
							i--;
						}
						PrintSeatMap(MovieTheaterMap, MapRow, MapCol);
					}
					
					WriteSeatMap(MyTheater, MovieTheaterMap, MapRow, MapCol);
					push(&StackTop, TicketLinkedListHead, ReceiptNumber, MyTheater->MovieTheaterName);
					TicketLinkedListHead = NULL;
					ReceiptNumber++;
					printf("\nThank you %s - enjoy your movie!\n", QueueHead->name);
					deQueue(&QueueHead);
				}
				break;
			case 2 : 
				printf("\n\nCustomer Queue\n\n");
				DisplayQueue(QueueHead);
				printf("\n\n");
				break;
			case 3 :
				PickAndDisplayTheater(BSTRoot, MovieTheaterMap, &MapRow, &MapCol);
				break;
			case 4 : 
				PrintReceipts(&StackTop);
				break;
			default :
				printf("Bad menu choice");
		}
	}
	
	printf("Good job - you sold tickets to all of the customers in line.\n");
	PrintReceipts(&StackTop);
	
	return 0;
}
